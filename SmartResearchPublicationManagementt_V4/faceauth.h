#ifndef FACEAUTH_H
#define FACEAUTH_H

#include <opencv2/opencv.hpp>
#include <QString>

class FaceAuth {
public:
    FaceAuth(); // Le constructeur

    // CETTE LIGNE DOIT ÊTRE EXACTEMENT COMME ÇA :
    bool identifierUtilisateur(const QString& employeeID);

private:
    cv::CascadeClassifier faceCascade;
};

#endif
