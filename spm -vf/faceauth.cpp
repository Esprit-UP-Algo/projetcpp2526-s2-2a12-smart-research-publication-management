#include "faceauth.h"
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QDebug>

FaceAuth::FaceAuth() {
}

QByteArray FaceAuth::capturerImageVisage() const
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        qDebug() << "Erreur: Caméra inaccessible.";
        return QByteArray();
    }

    cv::Mat frame;
    for(int i = 0; i < 10; i++) cap >> frame; // Stabilisation rapide
    cap.release();
    cv::destroyAllWindows();

    if (frame.empty()) {
        return QByteArray();
    }

    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf);
    return QByteArray(reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()));
}

bool FaceAuth::verifierAvecImage(const QByteArray& imageData, const QString& username) const
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"face\"; filename=\"face.jpg\""));
    imagePart.setBody(imageData);

    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
    namePart.setBody(username.toUtf8());

    multiPart->append(imagePart);
    multiPart->append(namePart);

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkRequest request(QUrl("http://127.0.0.1:5000/verify"));

    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool result = false;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        result = json.value("verified").toBool();
        qDebug() << "Réponse IA Vortex pour" << username << ":" << result;
    } else {
        qDebug() << "Serveur Vortex non détecté:" << reply->errorString();
        result = false;
    }

    reply->deleteLater();
    return result;
}

bool FaceAuth::identifierUtilisateur(const QString& username)
{
    const QByteArray imageData = capturerImageVisage();
    if (imageData.isEmpty()) {
        qDebug() << "FaceID: capture caméra impossible.";
        return false;
    }
    return verifierAvecImage(imageData, username);
}

bool FaceAuth::identifierUtilisateurParListe(const QStringList& usernames, QString *matchedUsername)
{
    if (matchedUsername) {
        matchedUsername->clear();
    }

    const QByteArray imageData = capturerImageVisage();
    if (imageData.isEmpty()) {
        qDebug() << "FaceID: capture caméra impossible (mode autonome).";
        return false;
    }

    for (const QString &username : usernames) {
        if (verifierAvecImage(imageData, username)) {
            if (matchedUsername) {
                *matchedUsername = username;
            }
            return true;
        }
    }

    return false;
}
