#include "faceauth.h"
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
// IL FAUT ABSOLUMENT CETTE PARTIE :
FaceAuth::FaceAuth() {
    // Constructeur vide, mais il doit exister !
}
bool FaceAuth::identifierUtilisateur(const QString& username) {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return false;

    cv::Mat frame;
    for(int i = 0; i < 15; i++) { // Stabilisation lumière
        cap >> frame;
        cv::flip(frame, frame, 1);
        cv::imshow("Authentification FaceID...", frame);
        cv::waitKey(30);
    }
    cv::destroyAllWindows();
    if (frame.empty()) return false;

    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf);
    QByteArray imageData(reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()));

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Envoi du Username
    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
    namePart.setBody(username.toUtf8());

    // Envoi de l'image
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"face\"; filename=\"face.jpg\""));
    imagePart.setBody(imageData);

    multiPart->append(namePart);
    multiPart->append(imagePart);

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.post(QNetworkRequest(QUrl("http://127.0.0.1:5000/verify")), multiPart);
    multiPart->setParent(reply);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool result = false;
    if (reply->error() == QNetworkReply::NoError) {
        result = QJsonDocument::fromJson(reply->readAll()).object().value("verified").toBool();
    }

    reply->deleteLater();
    cap.release();
    return result;
}
