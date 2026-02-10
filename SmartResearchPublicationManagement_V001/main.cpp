#include "smartresearchpublicationmanagement.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;

    // On lance le popup. exec() bloque la suite tant que le popup est ouvert.
    if (login.exec() == QDialog::Accepted) {
        // Si la connexion est réussie, on ouvre la fenêtre principale
        SmartResearchPublicationManagement w;
        w.show();
        return a.exec();
    }

    // Si on ferme le popup sans se connecter, le programme s'arrête ici
    return 0;
}
