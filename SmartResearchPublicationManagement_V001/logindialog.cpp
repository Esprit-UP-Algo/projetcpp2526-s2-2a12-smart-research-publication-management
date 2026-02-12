#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->btnLogin->setCursor(Qt::PointingHandCursor);
    ui->Quitter->setCursor(Qt::PointingHandCursor);


    // 1. Configuration du mot de passe
    ui->lePassword->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Connexion - Smart Research");

    // 2. Application du STYLE CSS (QSS)
    this->setStyleSheet(R"(
/* Dialog */
QDialog#LoginDialog{
    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,
        stop:0 #f2fbfb,
        stop:1 #e6f7f7);
    font-family: Consolas;
}

/* Card */
QGroupBox#groupBox_2{
    background: rgba(255,255,255,220);
    border-radius: 22px;
    border: 1px solid rgba(0,206,209,90);
}

/* Title */
QLabel#label{
    color:#004D40;
    font-size:24pt;
    font-weight:900;
}

/* Inputs */
QLineEdit{
    background: white;
    border: 1.5px solid rgba(0,206,209,120);
    border-radius: 18px;
    padding: 12px 18px;
    font-size: 12pt;
}
QLineEdit:focus{
    border: 2px solid #00CED1;
}

/* Buttons */
QPushButton#btnLogin{
    background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
        stop:0 #00CED1,
        stop:1 #7FFFD4);
    border:none;
    border-radius: 20px;
    padding: 12px 20px;
    font-size: 12pt;
    font-weight:900;
}
QPushButton#btnLogin:hover{
    opacity:0.9;
}

QPushButton#Quitter{
    background: rgba(0,77,64,12);
    border: 1px solid rgba(0,77,64,50);
    border-radius: 20px;
    padding: 12px 20px;
}

    )");

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


    if (user == "1" && pass == "1") {
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

