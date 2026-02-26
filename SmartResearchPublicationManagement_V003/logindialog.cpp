#include "logindialog.h"
#include "ui_logindialog.h"
#include "employe.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QCryptographicHash>  // Pour le hash SHA256
#include <QSqlQuery>
#include <QSqlError>

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

    // Hash du password saisi
    QString passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    // Vérification en base via Employe
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE FROM EMPLOYES WHERE USERNAME = :username AND PASSWORD_HASH = :passwordHash");
    query.bindValue(":username", username);
    query.bindValue(":passwordHash", passwordHash);

    if (!query.exec()) {
        QString error = query.lastError().text();
        qDebug() << "Erreur login SQL :" << error;
        QMessageBox::critical(this, "Erreur base", "Impossible de vérifier les identifiants :\n" + error);
        return;
    }

    if (query.next()) {
        // Login OK
        m_empId = query.value(0).toInt();
        accept();  // Ferme le dialog avec succès
    } else {
        QMessageBox::critical(this, "Accès Refusé", "Nom d'utilisateur ou mot de passe incorrect.");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    }
}

void LoginDialog::on_Quitter_clicked()
{
    qApp->exit(0);
}
