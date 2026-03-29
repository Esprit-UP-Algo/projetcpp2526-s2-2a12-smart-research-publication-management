#ifndef FACEAUTH_H
#define FACEAUTH_H

#include <opencv2/opencv.hpp>
#include <QString>

class FaceAuth {
public:
<<<<<<< HEAD

    FaceAuth(); // <-- Vérifie que cette ligne est bien là !
    bool identifierUtilisateur(const QString& employeeID);
=======
    FaceAuth(); // Le constructeur

    // CETTE LIGNE DOIT ÊTRE EXACTEMENT COMME ÇA :
    bool identifierUtilisateur(const QString& employeeID);

>>>>>>> 30b3d73efc0a4d3e01011549819f8cf3b40fa692
private:
    cv::CascadeClassifier faceCascade;
};

#endif
