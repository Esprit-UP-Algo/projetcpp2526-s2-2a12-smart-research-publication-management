#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // ===== CONFIGURATION =====
    ui->leUsername->setPlaceholderText("IDENTIFIANT CHERCHEUR");
    ui->lePassword->setPlaceholderText("CODE SÉCURISÉ");
    ui->lePassword->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Access Terminal - Smart Research");

    // ===== STYLE GLOBAL =====
    this->setStyleSheet(

        /* Police globale */
        "* { font-family: 'Consolas'; }"

        /* Fenêtre principale */
        "QDialog {"
        "   background-image: url(':/images/background.jpg');"
        "   background-position: center;"
        "   background-repeat: no-repeat;"
        "   border: 2px solid #00CED1;"
        "   border-radius: 25px;"
        "}"

        /* ===== LABELS ===== */
        "QLabel {"
        "   color: #ffffff;"
        "   font-size: 22px;"
        "   font-weight: 700;"
        "   letter-spacing: 2px;"
        "   background: transparent;"
        "   padding: 4px 0px;"
        "}"

        /* ===== CHAMPS DE SAISIE ===== */
        "QLineEdit {"
        "   background-color: rgba(0, 0, 0, 0.75);"
        "   border: 1px solid rgba(255, 255, 255, 0.2);"
        "   border-radius: 12px;"
        "   padding: 14px;"
        "   color: #00CED1;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"

        "QLineEdit:focus {"
        "   border: 2px solid #00CED1;"
        "   background-color: #000000;"
        "}"

        /* ===== BOUTON LOGIN (TRANSPARENT NÉON) ===== */
        "QPushButton#btnLogin {"
        "   background: transparent;"
        "   color: #00CED1;"
        "   border: 2px solid #00CED1;"
        "   border-radius: 12px;"
        "   padding: 14px;"
        "   font-size: 18px;"
        "   font-weight: 900;"
        "   text-transform: uppercase;"
        "}"

        "QPushButton#btnLogin:hover {"
        "   background: rgba(0, 206, 209, 0.15);"
        "}"

        "QPushButton#btnLogin:pressed {"
        "   background: rgba(0, 206, 209, 0.25);"
        "}"

        /* ===== BOUTON QUITTER ===== */
        "QPushButton#Quitter {"
        "   background: transparent;"
        "   color: #ffffff;"
        "   border: 1px solid rgba(255,255,255,0.4);"
        "   border-radius: 12px;"
        "   padding: 10px;"
        "   font-weight: bold;"
        "}"

        "QPushButton#Quitter:hover {"
        "   border: 1px solid #ff4757;"
        "   color: #ff4757;"
        "}"
        );

    // ===== EFFET GLOW GLOBAL =====
    QGraphicsDropShadowEffect *glow = new QGraphicsDropShadowEffect(this);
    glow->setBlurRadius(80);
    glow->setXOffset(0);
    glow->setYOffset(0);
    glow->setColor(QColor(0, 206, 209, 160));
    this->setGraphicsEffect(glow);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// ===== LOGIN =====
void LoginDialog::on_btnLogin_clicked()
{
    if (ui->leUsername->text() == "admin" &&
        ui->lePassword->text() == "admin")
    {
        accept();
    }
    else
    {
        ui->lePassword->setStyleSheet(
            "border: 2px solid #ff4757;"
            "background: rgba(255, 71, 87, 0.2);"
            "color: white;"
            "border-radius: 12px;"
            "padding: 14px;"
            );

        QMessageBox::critical(this,
                              "TERMINAL",
                              "Identifiants non autorisés.");
    }
}

// ===== QUITTER =====
void LoginDialog::on_Quitter_clicked()
{
    qApp->quit();
}
