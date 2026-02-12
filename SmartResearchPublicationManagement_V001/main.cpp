#include "smartresearchpublicationmanagement.h"
#include "logindialog.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;

    // ===== Load QSS =====
    QFile styleFile(":/styles/light.qss"); // si via .qrc
    // QFile styleFile("styles/light.qss"); // si fichier direct

    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&styleFile);
        a.setStyleSheet(ts.readAll());
        styleFile.close();
    }

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
