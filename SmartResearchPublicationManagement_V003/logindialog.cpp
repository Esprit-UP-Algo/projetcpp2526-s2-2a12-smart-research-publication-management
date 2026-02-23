#include "logindialog.h"
#include "ui_logindialog.h"
#include "employe.h"           // ← ta classe Employe (avec verifierLogin)
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QCryptographicHash>  // SHA256
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    ui->leUsername->setFocus();
    ui->btnLogin->setCursor(Qt::PointingHandCursor);
    ui->Quitter->setCursor(Qt::PointingHandCursor);

    // Masquer le mot de passe
    ui->lePassword->setEchoMode(QLineEdit::Password);

    this->setWindowTitle("Connexion - Smart Research");

    // STYLE CSS (QSS) – exactement comme le tien
    this->setStyleSheet(R"(
        QDialog#LoginDialog{
            background: qlineargradient(x1:0,y1:0,x2:1,y2:1,
                stop:0 #f2fbfb,
                stop:1 #e6f7f7);
            font-family: Consolas;
        }
        QGroupBox#groupBox_2{
            background: rgba(255,255,255,220);
            border-radius: 22px;
            border: 1px solid rgba(0,206,209,90);
        }
        QLabel#label{
            color:#004D40;
            font-size:24pt;
            font-weight:900;
        }
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

    // Ombre portée pour effet moderne
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(5);
    shadow->setColor(QColor(0, 0, 0, 60));
    this->setGraphicsEffect(shadow);

    // Fenêtre propre (pas de bouton maximize/minimize inutile)
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text().trimmed();
    QString password = ui->lePassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Remplissez tous les champs");
        ui->leUsername->setFocus();
        return;
    }

    QString passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    QString id, role, err;
    if (Employe::verifierLogin(username, passwordHash, id, role, &err)) {
        m_idEmploye = id;
        m_role = role;
        accept();
    } else {
        QMessageBox::critical(this, "Erreur", err.isEmpty() ? "Identifiants incorrects" : err);
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}

void LoginDialog::on_Quitter_clicked()
{
    reject();  // Ferme le dialog sans succès (QDialog::Rejected)
}
