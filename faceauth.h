#ifndef FACEAUTH_H
#define FACEAUTH_H

#include <QString>
#include <QProcess>
#include <QNetworkAccessManager>

class FaceAuth {
public:
    FaceAuth(); // Constructeur

    // La fonction principale que tu appelles dans ton Login
    bool identifierUtilisateur(const QString& username);

private:
    // Vérifie si le serveur Python tourne, sinon le lance
    void assurerServeurActif();

    // "static" permet au serveur de rester ouvert même si l'objet FaceAuth est détruit
    static QProcess* processIA;
};

#endif // FACEAUTH_H
