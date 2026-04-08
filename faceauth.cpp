#include "faceauth.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

// CORRECTION : Définition du constructeur
FaceAuth::FaceAuth() {}

bool FaceAuth::identifierUtilisateur(const QString& employeeID) {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return false;

    cv::Mat frame;
    for(int i = 0; i < 30; i++) {
        cap >> frame;
        if (frame.empty()) continue;
        cv::flip(frame, frame, 1);
        cv::imshow("Scan FaceID - Cadrez votre visage", frame);
        if (cv::waitKey(30) >= 0) break;
    }
    cv::destroyAllWindows();

    if (frame.empty()) {
        cap.release();
        return false;
    }

    // Encodage JPG
    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf);
    QByteArray imageData(reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()));

    // Envoi HTTP
    QNetworkAccessManager manager;
    QEventLoop loop;
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart idPart;
    idPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
    idPart.setBody(employeeID.toUtf8());

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"face\"; filename=\"face.jpg\""));
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setBody(imageData);

    multiPart->append(idPart);
    multiPart->append(imagePart);

    QNetworkRequest request(QUrl("http://127.0.0.1:5000/verify"));
    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool isVerified = false;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
        isVerified = json.object().value("verified").toBool();
        qDebug() << "FaceID Score Result:" << isVerified;
    } else {
        qDebug() << "Erreur Réseau:" << reply->errorString();
    }

    reply->deleteLater();
    cap.release();
    return isVerified;
}
