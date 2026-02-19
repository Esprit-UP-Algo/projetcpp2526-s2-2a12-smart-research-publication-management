#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include "connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection& c = Connection::createInstance();
    bool test = c.createConnection();
        if (test) {
        QMessageBox::information(
            nullptr,
            QObject::tr("Basededonnées"),
            QObject::tr("Connexion réussite.\nCliquez sur Annuler pour  quitter."),
            QMessageBox::Cancel
            );
    }
    else
    {
        QMessageBox::critical(
            nullptr,
            QObject::tr("Erreur"),
            QObject::tr("Connexion à la base impossible !"),
            QMessageBox::Cancel
            );
    }
    LoginDialog login;
    // On lance le popup. exec() bloque la suite tant que le popup est ouvert.
    if (login.exec() == QDialog::Accepted) {
        // Si la connexion est réussie, on ouvre la fenêtre principale
        MainWindow w;
        w.show();
        return a.exec();
    }

    // Si on ferme le popup sans se connecter, le programme s'arrête ici
    return 0;
}

