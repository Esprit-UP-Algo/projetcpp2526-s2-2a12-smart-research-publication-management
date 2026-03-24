#include "logindialog.h"
#include "ui_logindialog.h"
#include "employe.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QCryptographicHash>  // Pour le hash SHA256
#include <QSqlQuery>
#include <QSqlError>
#include "faceauth.h"

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

    // Application du STYLE CSS (QSS)
    this->setStyleSheet(R"(
        /* Dialog */
        QDialog#LoginDialog{
            background: qlineargradient(x1:0,y1:0,x2:1,y2:1,
                stop:0 #f2fbfb,
                stop:1 #e6f7f7);
            font-family: Consolas;
        }
/* Bouton Face ID */
QPushButton#btnFaceID {
    background: white;
    border: 2px solid #00CED1;
    border-radius: 20px;
    color: #004D40;
    font-weight: 900;
    padding: 10px;
}
QPushButton#btnFaceID:hover {
    background: #e6f7f7;
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

    // Ajout ombre portée
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(5);
    shadow->setColor(QColor(0, 0, 0, 60));
    this->setGraphicsEffect(shadow);

    // Fenêtre propre
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
        QMessageBox::warning(this, "Champs manquants", "Veuillez entrer votre nom d'utilisateur et mot de passe.");
        ui->leUsername->setFocus();
        return;
    }

    // 1. On prépare le hash du mot de passe (SHA256 comme dans ta version)
    QString passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    // 2. On utilise la méthode statique de la classe Employe
    // Elle va vérifier en BD ET remplir Session::instance() d'un seul coup
    QString errorMsg;
    if (Employe::authentifier(username, passwordHash, &errorMsg)) {
        // Succès ! La session est maintenant remplie (ID, Nom, Rôle)
        accept();  // Ferme le dialog et renvoie QDialog::Accepted
    } else {
        // Échec (mauvais pass ou erreur SQL)
        QMessageBox::critical(this, "Accès Refusé", errorMsg);
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}
void LoginDialog::on_btnFaceID_clicked()
{
    QString user = ui->leUsername->text().trimmed();

    if (user.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir votre username.");
        return;
    }

    FaceAuth auth;
    // 1. Reconnaissance faciale OpenCV
    if (auth.identifierUtilisateur(user)) {

        QString errorMsg;
        // 2. Initialisation de la session (C'est ici que le rôle est fixé)
        if (Employe::authentifierFaceID(user, &errorMsg)) {

            // 3. REDIRECTION IDENTIQUE
            // On ferme le dialogue, le main.cpp lancera MainWindow
            this->accept();

        } else {
            QMessageBox::critical(this, "Erreur Session", errorMsg);
        }
    } else {
        QMessageBox::critical(this, "Échec", "Visage non reconnu pour " + user);
    }
}
