#ifndef FACEAUTH_H
#define FACEAUTH_H

#include <opencv2/opencv.hpp>
#include <QString>

class FaceAuth {
public:

    FaceAuth(); // <-- Vérifie que cette ligne est bien là !
    bool identifierUtilisateur(const QString& employeeID);
private:
    cv::CascadeClassifier faceCascade;
};

#endif
