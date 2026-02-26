#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // 1) Connexion DB (avant tout CRUD)
    Connection* c = Connection::instance();
    if (!c->createConnect()) {
        QMessageBox::critical(nullptr, "Erreur", "Connexion à la base impossible !");
        return 0;
    }

    // 2) Login
    LoginDialog login;
    if (login.exec() != QDialog::Accepted) {
        c->closeConnection();
        return 0;
    }


    // 3) MainWindow
    MainWindow w(login.empId());
    w.show();

    int ret = a.exec();

    // 4) Fermeture DB
    c->closeConnection();

    // ⚠️ Optionnel (souvent je conseille de le supprimer pour éviter warning "still in use")
    // QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    return ret;
}
