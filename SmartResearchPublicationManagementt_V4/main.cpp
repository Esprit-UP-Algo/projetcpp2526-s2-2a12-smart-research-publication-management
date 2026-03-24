#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    // Indispensable pour l'interface Qt
    QApplication a(argc, argv);

    // 1) Connexion à la Base de Données
    // On récupère l'instance unique (Singleton)
    Connection* c = Connection::instance();
    if (!c->createConnect()) {
        QMessageBox::critical(nullptr, "Erreur Fatale",
                              "Impossible d'établir une connexion avec la base de données.\n"
                              "Vérifiez vos paramètres réseau ou SQL.");
        return -1; // On quitte avec un code d'erreur
    }

    // 2) Lancement du Login (Classique + FaceID)
    LoginDialog login;

    /* Le .exec() bloque ici tant que l'utilisateur n'a pas réussi
       son login (bouton Connect ou Scan Face réussi).
       Dès que ton code appelle 'accept()', exec() renvoie QDialog::Accepted.
    */
    if (login.exec() != QDialog::Accepted) {
        // Si l'utilisateur ferme la fenêtre sans se connecter
        c->closeConnection();
        return 0;
    }

    // 3) Ouverture de la fenêtre principale
    // On n'arrive ici que si le Scan FaceID ou le Login a fonctionné
    MainWindow w;
    w.show();

    // Boucle d'événements principale
    int ret = a.exec();

    // 4) Nettoyage avant de quitter
    c->closeConnection();

    return ret;
}
