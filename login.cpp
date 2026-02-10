#include "login.h"
#include "ui_login.h"
#include "usermang.h"     // ← très important : inclure la fenêtre principale
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text().trimmed();
    QString password = ui->lePassword->text().trimmed();

    // Simulation (à changer plus tard par ta vraie vérification)
    if (username == "admin" && password == "1234") {
        // Succès : ouvre la page principale
        UserMang *principal = new UserMang();
        principal->show();

        // Ferme la fenêtre login
        this->close();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}
