#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection* c = Connection::instance();
    bool test = c->createConnect();

    if (test) {
        QMessageBox::information(nullptr,
                                 QObject::tr("Base de données"),
                                 QObject::tr("Connexion réussie."),
                                 QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr,
                              QObject::tr("Erreur"),
                              QObject::tr("Connexion à la base impossible !"),
                              QMessageBox::Ok);
        // si tu veux arrêter direct:
        // return 0;
    }

    int ret = 0;

    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        ret = a.exec();     // ✅ pas de return ici
    } else {
        ret = 0;
    }

    // ✅ IMPORTANT: fermer puis removeDatabase AVANT de sortir
    c->closeConnection();

    // Si ta connexion est "default" (addDatabase sans nom)
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    return ret;
}
