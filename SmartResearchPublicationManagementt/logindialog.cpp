#include "logindialog.h"
#include "ui_logindialog.h"
#include "employe.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QCryptographicHash>  // Pour le hash SHA256
#include <QSqlQuery>
#include <QSqlError>
#include "faceauth.h"
#include <QInputDialog>

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

    ui->leUsername->setPlaceholderText(QStringLiteral("Identifiant (ex. fourni par le RH)"));
    ui->lePassword->setPlaceholderText(QStringLiteral("Mot de passe du compte"));
    ui->leUsername->setToolTip(QStringLiteral("Saisissez le nom d’utilisateur attribué à votre compte employé."));
    ui->lePassword->setToolTip(QStringLiteral("Saisissez le mot de passe associé à cet identifiant."));
    ui->btnLogin->setToolTip(QStringLiteral("Valide la connexion avec les identifiants saisis."));
    ui->btnForgotPass->setToolTip(
        QStringLiteral("Si vous avez oublié le mot de passe : vous devrez confirmer votre identifiant et votre CIN, "
                        "puis choisir un nouveau mot de passe conforme aux règles de sécurité (mot de passe fort)."));
    ui->btnFaceID->setToolTip(QStringLiteral("Connexion par reconnaissance faciale (après avoir saisi l’identifiant)."));
    ui->Quitter->setToolTip(QStringLiteral("Fermer la fenêtre de connexion."));

    this->setWindowTitle("Connexion - Smart Research");

    // Style "Soft Minimalism" (Inspiré du code HTML/CSS fourni, avec écriture Noire)
    this->setStyleSheet(R"(
        QDialog#LoginDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, 
                                        stop:0 #faf9f6, stop:0.5 #f5f3f0, stop:1 #f0ede8);
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Inter', system-ui, sans-serif;
        }
        
        QGroupBox#groupBox_2 {
            background-color: rgba(255, 255, 255, 220);
            border: 1px solid rgba(255, 255, 255, 100);
            border-radius: 32px;
        }
        
        QLabel#label {
            color: #2c1e16;
            font-size: 38px; /* Plus grand pour l'effet WOW */
            font-weight: 900;
            letter-spacing: -1.5px;
            background: transparent;
        }
        
        QLineEdit {
            background-color: rgba(255, 255, 255, 200);
            border: 1.5px solid rgba(240, 206, 170, 100);
            border-radius: 16px;
            padding: 16px 16px;
            color: #000000;
            font-size: 15px;
            font-weight: 500;
        }
        QLineEdit:focus {
            border: 1.5px solid #f0ceaa;
            background-color: #ffffff;
        }
        
        QLabel#label_2, QLabel#label_3 {
            color: #4a3728;
            font-size: 13px;
            font-weight: 700;
            background: transparent;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }
        
        QPushButton#btnLogin {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f0ceaa, stop:1 #e0be9c);
            border: none;
            border-radius: 16px;
            padding: 14px;
            color: #2c1e16;
            font-size: 18px;
            font-weight: 800;
            letter-spacing: 0.5px;
        }
        QPushButton#btnLogin:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ebc49a, stop:1 #dbb88c);
            box-shadow: 0 4px 15px rgba(240, 206, 170, 0.4);
        }
        
        QPushButton#Quitter {
            background-color: #ffffff;
            border: 1.5px solid rgba(240, 206, 170, 120);
            border-radius: 16px;
            padding: 12px;
            color: #2c1e16;
            font-size: 14px;
            font-weight: 700;
        }
        
        QPushButton#btnFaceID, QPushButton#btnForgotPass {
            background: transparent;
            border: none;
            color: #8b6655;
            font-size: 13px;
            font-weight: 700;
        }
        QPushButton#btnForgotPass {
            text-align: right;
        }
        QPushButton#btnFaceID:hover, QPushButton#btnForgotPass:hover {
            color: #2c1e16;
            text-decoration: underline;
        }
    )");

    /* Changer le texte "Log in" par quelque chose de plus accueillant */
    if(QLabel* titleLabel = this->findChild<QLabel*>("label")) {
        titleLabel->setText("Bienvenue");
    }

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
void LoginDialog::on_btnFaceID_clicked() {
    QString user = ui->leUsername->text().trimmed();
    if (user.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Saisissez votre nom !");
        return;
    }

    FaceAuth auth;
    // 1. Appel de l'IA (Python)
    if (auth.identifierUtilisateur(user)) {
        QString errorMsg;
        // 2. Appel de la Base de données (SQL)
        if (Employe::authentifierFaceID(user, &errorMsg)) {
            this->accept(); // Succès total !
        } else {
            QMessageBox::critical(this, "Erreur SQL", errorMsg);
        }
    } else {
        // C'est ici que s'affiche l'image que tu m'as montrée
        QMessageBox::critical(this, "Échec IA", "Visage non reconnu");
    }
}

void LoginDialog::on_Quitter_clicked()
{
    this->reject(); // Ferme la fenêtre proprement
}


void LoginDialog::on_btnForgotPass_clicked()
{
    bool ok;

    // 1. Vérification de l'identité
    QString username = QInputDialog::getText(this, "Récupération", "Nom d'utilisateur :", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) return;

    QString cin = QInputDialog::getText(this, "Vérification", "Numéro de CIN :", QLineEdit::Normal, "", &ok);
    if (!ok || cin.isEmpty()) return;

    QSqlQuery query;
    query.prepare("SELECT NOM FROM EMPLOYES WHERE USERNAME = :user AND CIN = :cin");
    query.bindValue(":user", username);
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        // 2. Nouveau mot de passe (même règle de force que la création de compte)
        QString newPass;
        for (;;) {
            newPass = QInputDialog::getText(this, "Succès",
                                            "Identité confirmée. Entrez un mot de passe fort (min. 10 car., "
                                            "minuscules, majuscules, chiffres, caractère spécial) :",
                                            QLineEdit::Password, "", &ok);
            if (!ok || newPass.isEmpty())
                return;
            if (Employe::motDePasseAcceptable(newPass))
                break;
            QMessageBox::warning(this, "Mot de passe trop faible",
                                 "Le mot de passe doit atteindre au moins le niveau « Fort » "
                                 "(comme à la création de compte employé). Réessayez.");
        }

        QByteArray hashedPass = QCryptographicHash::hash(newPass.toUtf8(), QCryptographicHash::Sha256).toHex();

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE EMPLOYES SET PASSWORD_HASH = :pass WHERE USERNAME = :user");
        updateQuery.bindValue(":pass", QString(hashedPass));
        updateQuery.bindValue(":user", username);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Succès", "Mot de passe mis à jour avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de mettre à jour la base de données.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Username ou CIN incorrect.");
    }
}
