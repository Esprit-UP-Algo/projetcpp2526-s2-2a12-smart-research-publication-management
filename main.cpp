#include "mainwindow.h"
#include "logindialog.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    // Configuration de l'application
    QApplication a(argc, argv);

    // 1) Connexion à la Base de Données (Singleton)
    Connection* c = Connection::instance();
    if (!c->createConnect()) {
        QMessageBox::critical(nullptr, "Erreur Fatale",
                              "Impossible d'établir une connexion avec la base de données.\n"
                              "Vérifiez vos paramètres réseau ou SQL.");
        return -1;
    }

    // 2) Lancement du Login (Classique + FaceID)
    LoginDialog login;

    // .exec() est bloquant : il attend que login.accept() ou login.reject() soit appelé
    if (login.exec() != QDialog::Accepted) {
        // Si l'utilisateur annule ou ferme la fenêtre de login
        c->closeConnection();
        return 0;
    }

    // 3) Ouverture de la fenêtre principale
    // On n'instancie MainWindow qu'après la réussite du login pour économiser les ressources
    MainWindow w;
    w.show();

    // Boucle d'événements principale
    int ret = a.exec();

    // 4) Nettoyage avant fermeture
    c->closeConnection();

    return ret;
}
