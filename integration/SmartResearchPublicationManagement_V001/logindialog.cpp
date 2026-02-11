#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 1. Configuration du mot de passe
    ui->lePassword->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Connexion - Smart Research");

    // 2. Application du STYLE CSS (QSS)
    this->setStyleSheet(
        "QDialog {"
        "   background-color: #ffffff;"
        "   border-radius: 10px;"
        "}"
        "QLabel {"
        "   font-family: 'Segoe UI', sans-serif;"
        "   color: #2c3e50;"
        "   font-size: 13px;"
        "}"
        "QLineEdit {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 6px;"
        "   padding: 8px 12px;"
        "   font-size: 14px;"
        "   color: #495057;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #3498db;"
        "   background-color: #ffffff;"
        "}"
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 10px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #21618c;"
        "}"
        );

    // 3. Ajout d'une ombre portée pour l'effet "Popup"
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(5);
    shadow->setColor(QColor(0, 0, 0, 60));
    this->setGraphicsEffect(shadow);

    // On rend la fenêtre un peu plus "propre"
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnLogin_clicked()
{
    QString user = ui->leUsername->text();
    QString pass = ui->lePassword->text();

    if (user == "admin" && pass == "admin") {
        accept();
    } else {
        QMessageBox::critical(this, "Accès Refusé", "Identifiants invalides.");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}

void LoginDialog::on_Quitter_clicked()
{
    // Cette ligne ferme toutes les fenêtres et arrête le programme Qt
    qApp->exit(0);
}

