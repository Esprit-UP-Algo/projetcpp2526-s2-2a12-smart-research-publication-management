#ifndef FACEAUTH_H
#define FACEAUTH_H

#include <opencv2/opencv.hpp>
#include <QString>
#include <QStringList>
#include <QByteArray>

class FaceAuth {
public:

    FaceAuth();
    bool identifierUtilisateur(const QString& username);
    bool identifierUtilisateurParListe(const QStringList& usernames, QString *matchedUsername);
private:
    QByteArray capturerImageVisage() const;
    bool verifierAvecImage(const QByteArray& imageData, const QString& username) const;
    cv::CascadeClassifier faceCascade;
};

#endif
