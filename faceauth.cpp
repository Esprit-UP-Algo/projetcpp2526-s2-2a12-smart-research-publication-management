#include "faceauth.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

FaceAuth::FaceAuth() {
    QString xmlPath = QCoreApplication::applicationDirPath() + "/haarcascade_frontalface_default.xml";
    if (!faceCascade.load(xmlPath.toStdString())) {
        qDebug() << "!!! ERREUR : XML introuvable dans" << xmlPath;
    }
}

bool FaceAuth::identifierUtilisateur(const QString& employeeID) {
    if (faceCascade.empty()) return false;

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return false;

    // 1. CHARGEMENT DE TA PHOTO
    QString photoPath = QCoreApplication::applicationDirPath() + "/faces/" + employeeID + ".jpg";
    cv::Mat refImg = cv::imread(photoPath.toStdString(), cv::IMREAD_GRAYSCALE);

    if (refImg.empty()) {
        qDebug() << "ERREUR : Photo introuvable ->" << photoPath;
        cap.release();
        return false;
    }

    cv::resize(refImg, refImg, cv::Size(150, 150));
    cv::equalizeHist(refImg, refImg);

    cv::Mat frame, gray;
    // Boucle principale de capture
    for (int i = 0; i < 300; i++) {
        cap >> frame;
        if (frame.empty()) continue;

        cv::flip(frame, frame, 1);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 8, 0, cv::Size(100, 100));

        // Boucle sur les visages détectés
        for (const auto& area : faces) {
            cv::Mat faceROI = gray(area);
            cv::resize(faceROI, faceROI, cv::Size(150, 150));
            cv::equalizeHist(faceROI, faceROI);

            // --- CALCUL DE SÉCURITÉ ---
            cv::Mat result;
            cv::matchTemplate(faceROI, refImg, result, cv::TM_CCOEFF_NORMED);
            double maxVal;
            cv::minMaxLoc(result, nullptr, &maxVal);

            cv::Mat diff; // Déclaré une seule fois ici
            cv::absdiff(faceROI, refImg, diff);
            cv::Scalar meanDiff = cv::mean(diff);

            int scoreMatch = static_cast<int>(maxVal * 100);

            // LOGIQUE DE VALIDATION
            if (scoreMatch > 45 && meanDiff[0] < 60) {
                qDebug() << ">>> MATCH REUSSI !";
                cv::rectangle(frame, area, cv::Scalar(0, 255, 0), 3);
                cv::putText(frame, "ACCES VALIDE", cv::Point(area.x, area.y-10), 0, 0.7, cv::Scalar(0, 255, 0), 2);
                cv::imshow("Vortex FaceID", frame);
                cv::waitKey(2000);
                cap.release();
                cv::destroyAllWindows();
                return true;
            } else {
                // Si ce n'est pas le bon utilisateur
                cv::rectangle(frame, area, cv::Scalar(0, 0, 255), 2);
                cv::putText(frame, "INCONNU", cv::Point(area.x, area.y-10), 0, 0.7, cv::Scalar(0, 0, 255), 2);
            }
        } // Fin de la boucle for (area)

        cv::imshow("Verification Biometrique", frame);
        if (cv::waitKey(10) == 27) break; // Echap pour sortir

    } // Fin de la boucle for (i)

    cap.release();
    cv::destroyAllWindows();
    return false;
}
