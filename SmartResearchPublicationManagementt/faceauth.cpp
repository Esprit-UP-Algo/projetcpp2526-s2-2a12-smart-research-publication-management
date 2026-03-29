#include "faceauth.h"
<<<<<<< HEAD
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
=======
#include <QCoreApplication>
#include <QDebug>

FaceAuth::FaceAuth() {
    QString xmlPath = QCoreApplication::applicationDirPath() + "/haarcascade_frontalface_default.xml";
    if (!faceCascade.load(xmlPath.toStdString())) {
        qDebug() << "ERREUR XML:" << xmlPath;
    }
}

bool FaceAuth::identifierUtilisateur(const QString& employeeID) {
    if (faceCascade.empty()) return false;

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return false;

    // 📌 Charger image de référence
    QString photoPath = QCoreApplication::applicationDirPath() + "/faces/" + employeeID + ".jpg";
    cv::Mat refImg = cv::imread(photoPath.toStdString(), cv::IMREAD_GRAYSCALE);

    if (refImg.empty()) {
        qDebug() << "Image introuvable:" << photoPath;
>>>>>>> 30b3d73efc0a4d3e01011549819f8cf3b40fa692
        cap.release();
        return false;
    }

<<<<<<< HEAD
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
=======
    // 🔥 Prétraitement amélioré
    cv::resize(refImg, refImg, cv::Size(150, 150));
    cv::GaussianBlur(refImg, refImg, cv::Size(3,3), 0);
    cv::equalizeHist(refImg, refImg);

    cv::Mat frame, gray;

    for (int i = 0; i < 300; i++) {
        cap >> frame;
        if (frame.empty()) continue;

        cv::flip(frame, frame, 1);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 🔥 Amélioration image caméra
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 5, 0, cv::Size(100, 100));

        for (const auto& area : faces) {
            cv::Mat faceROI = gray(area);

            cv::resize(faceROI, faceROI, cv::Size(150, 150));
            cv::GaussianBlur(faceROI, faceROI, cv::Size(3,3), 0);
            cv::equalizeHist(faceROI, faceROI);

            // --- MATCH TEMPLATE ---
            cv::Mat result;
            cv::matchTemplate(faceROI, refImg, result, cv::TM_CCOEFF_NORMED);

            double maxVal;
            cv::minMaxLoc(result, nullptr, &maxVal);

            // --- DIFFÉRENCE ---
            cv::Mat diff;
            cv::absdiff(faceROI, refImg, diff);
            cv::Scalar meanDiff = cv::mean(diff);

            int scoreMatch = static_cast<int>(maxVal * 100);

            // 🔥 AJOUT STABILITÉ (moyenne sur plusieurs frames)
            static int successCount = 0;

            if (scoreMatch > 55 && meanDiff[0] < 50) {
                successCount++;

                if (successCount >= 5) { // 🔥 validation après plusieurs frames
                    qDebug() << "MATCH REUSSI";

                    cv::rectangle(frame, area, cv::Scalar(0, 255, 0), 3);
                    cv::putText(frame, "ACCES VALIDE",
                                cv::Point(area.x, area.y - 10),
                                cv::FONT_HERSHEY_SIMPLEX, 0.8,
                                cv::Scalar(0, 255, 0), 2);

                    cv::imshow("FaceID", frame);
                    cv::waitKey(1500);

                    cap.release();
                    cv::destroyAllWindows();
                    return true;
                }
            } else {
                successCount = 0;

                cv::rectangle(frame, area, cv::Scalar(0, 0, 255), 2);
                cv::putText(frame, "INCONNU",
                            cv::Point(area.x, area.y - 10),
                            cv::FONT_HERSHEY_SIMPLEX, 0.8,
                            cv::Scalar(0, 0, 255), 2);
            }
        }

        cv::imshow("Verification Biometrique", frame);

        if (cv::waitKey(10) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return false;
>>>>>>> 30b3d73efc0a4d3e01011549819f8cf3b40fa692
}
