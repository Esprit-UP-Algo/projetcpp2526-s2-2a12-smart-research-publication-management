#include "faceauth.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

FaceAuth::FaceAuth() {
    // 1. Chercher le fichier de détection dans le dossier de l'exécutable
    QString xmlPath = QCoreApplication::applicationDirPath() + "/haarcascade_frontalface_default.xml";

    if (!faceCascade.load(xmlPath.toStdString())) {
        qDebug() << "!!! ERREUR : Fichier XML introuvable à :" << xmlPath;
    } else {
        qDebug() << "Succès : Modèle de détection chargé.";
    }
}

bool FaceAuth::identifierUtilisateur(const QString& employeeID) {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return false;

    // --- PRÉPARATION DE LA PHOTO DE RÉFÉRENCE ---
    QString photoPath = QCoreApplication::applicationDirPath() + "/faces/" + employeeID + ".jpg";
    cv::Mat refImage = cv::imread(photoPath.toStdString(), cv::IMREAD_GRAYSCALE);

    if (refImage.empty()) {
        qDebug() << "!!! ERREUR : Photo introuvable à :" << photoPath;
        return false;
    }

    // Égalisation pour que la photo ne soit pas trop sombre/claire
    cv::equalizeHist(refImage, refImage);

    cv::Mat frame, gray;
    for (int i = 0; i < 200; i++) { // Environ 6-7 secondes de scan
        cap >> frame;
        if (frame.empty()) continue;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        // Égalisation du flux direct pour matcher avec la photo
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 5, 0, cv::Size(100, 100));

        for (const auto& area : faces) {
            // Extraction et redimensionnement
            cv::Mat faceROI = gray(area);
            cv::resize(faceROI, faceROI, refImage.size());

            // Comparaison
            cv::Mat result;
            cv::matchTemplate(faceROI, refImage, result, cv::TM_CCOEFF_NORMED);
            double minVal, maxVal;
            cv::minMaxLoc(result, &minVal, &maxVal);

            qDebug() << "SCORE : " << maxVal;

            // --- SEUIL AJUSTÉ À 0.25 (Plus réaliste pour matchTemplate) ---
            if (maxVal > 0.25) {
                qDebug() << "MATCH RÉUSSI !";
                cv::rectangle(frame, area, cv::Scalar(0, 255, 0), 4); // Rectangle Vert épais
                cv::imshow("Scan FaceID", frame);
                cv::waitKey(500); // Petite pause pour voir le succès
                cap.release();
                cv::destroyAllWindows();
                return true;
            }

            // Rectangle Rouge tant que ce n'est pas bon
            cv::rectangle(frame, area, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Scan FaceID - Restez face à l'objectif", frame);
        if (cv::waitKey(30) == 27) break; // Echap pour quitter
    }

    cap.release();
    cv::destroyAllWindows();
    return false;
}

