#include "faceauth.h"
#include <QCoreApplication>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <opencv2/opencv.hpp>

// Initialisation du pointeur statique (obligatoire en C++)
QProcess* FaceAuth::processIA = nullptr;

FaceAuth::FaceAuth() {}

void FaceAuth::assurerServeurActif() {
    QNetworkAccessManager testManager;
    QNetworkRequest request(QUrl("http://127.0.0.1:5000/")); // Test de ping sur Flask
    QEventLoop loop;
    QNetworkReply* reply = testManager.get(request);

    QTimer::singleShot(500, &loop, &QEventLoop::quit); // On n'attend pas plus de 0.5s
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Si le serveur ne répond pas (Erreur de connexion)
    if (reply->error() != QNetworkReply::NoError) {
        if (!processIA) processIA = new QProcess();

        if (processIA->state() == QProcess::NotRunning) {
            // Utilisation du chemin relatif vers le script (Très important pour le tuteur)
            QString scriptPath = QCoreApplication::applicationDirPath() + "/face_id_vortex.py";
            processIA->start("python", QStringList() << scriptPath);
            processIA->waitForStarted(2000);
            QThread::msleep(1500); // Laisse le temps à l'IA de charger les modèles
        }
    }
    reply->deleteLater();
}

bool FaceAuth::identifierUtilisateur(const QString& username) {
    assurerServeurActif();

    // 1. Capture Caméra
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return false;
    cv::Mat frame;
    for(int i=0; i<10; i++) cap >> frame; // Stabilisation
    cap.release();

    // 2. Encodage Image
    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf);
    QByteArray imageData(reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()));

    // 3. Envoi HTTP (Requête vers Flask)
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

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        return json.value("verified").toBool();
    }
    return false;
}
