#include "faceauth.h"
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QDebug>

FaceAuth::FaceAuth() {
    // Tentative de chargement du cascade classifier pour la détection locale (preview)
    // On essaie plusieurs chemins communs sur Windows
    QStringList paths = {
        "haarcascade_frontalface_default.xml",
        "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml",
        "C:/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/etc/haarcascades/haarcascade_frontalface_default.xml"
    };

    for (const QString &p : paths) {
        if (faceCascade.load(p.toStdString())) {
            qDebug() << "FaceID: Cascade charge depuis" << p;
            break;
        }
    }
}

QByteArray FaceAuth::capturerImageVisage()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        qDebug() << "Erreur: Caméra inaccessible.";
        return QByteArray();
    }

    cv::Mat frame;
    cv::Mat gray;
    std::vector<cv::Rect> faces;
    bool captured = false;
    int framesWithFace = 0;

    const std::string winName = "FaceID - Alignez votre visage (Q pour quitter)";
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::Mat displayFrame = frame.clone();
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        // Détection locale pour le rectangle vert (feedback utilisateur)
        if (!faceCascade.empty()) {
            faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(100, 100));
            for (const auto& r : faces) {
                cv::rectangle(displayFrame, r, cv::Scalar(0, 255, 0), 2);
            }

            if (!faces.empty()) {
                framesWithFace++;
                // Après ~15 frames avec un visage, on peut auto-capturer (pour le confort)
                if (framesWithFace > 20) {
                    captured = true;
                    break;
                }
            } else {
                framesWithFace = 0;
            }
        }

        cv::imshow(winName, displayFrame);
        
        int key = cv::waitKey(30);
        if (key == 'q' || key == 'Q' || key == 27) break; // Esc ou Q pour quitter
        if (key == ' ' || key == 13) { // Espace ou Entrée pour forcer la capture
            captured = true;
            break;
        }
    }

    cv::destroyWindow(winName);
    cap.release();

    if (!captured || frame.empty()) {
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
bool FaceAuth::enregistrerUtilisateur(const QString& username)
{
    const QByteArray imageData = capturerImageVisage();
    if (imageData.isEmpty()) {
        qDebug() << "FaceID (Enroll): capture caméra impossible.";
        return false;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"face\"; filename=\"ref.jpg\""));
    imagePart.setBody(imageData);

    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
    namePart.setBody(username.toUtf8());

    multiPart->append(imagePart);
    multiPart->append(namePart);

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkRequest request(QUrl("http://127.0.0.1:5000/enroll"));

    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool success = false;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        success = json.value("success").toBool();
        qDebug() << "Enregistrement IA Vortex pour" << username << ":" << success;
    } else {
        qDebug() << "Serveur Vortex non détecté (Enroll):" << reply->errorString();
    }

    reply->deleteLater();
    return success;
}
