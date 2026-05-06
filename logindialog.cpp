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
#include <QDateTime>
#include <QRandomGenerator>
#include <QSet>
#include "mailsender.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QThread>

namespace {
QProcess *g_faceServerProcess = nullptr;

bool isFaceServerReachable()
{
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 5000);
    const bool ok = socket.waitForConnected(400);
    if (ok) socket.disconnectFromHost();
    return ok;
}

QString ensureFaceScript()
{
    const QString scriptPath = QCoreApplication::applicationDirPath() + "/face_id_vortex.py";
    QFile file(scriptPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return QString();
    }

    QTextStream out(&file);
    out << "from flask import Flask, request, jsonify\n"
        << "import cv2\n"
        << "import numpy as np\n"
        << "import os\n\n"
        << "app = Flask(__name__)\n"
        << "face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')\n\n"
        << "@app.route('/health', methods=['GET'])\n"
        << "def health():\n"
        << "    return jsonify({'ok': True})\n\n"
        << "@app.route('/enroll', methods=['POST'])\n"
        << "def enroll():\n"
        << "    if 'face' in request.files:\n"
        << "        username = request.form.get('username', 'user')\n"
        << "        img = cv2.imdecode(np.frombuffer(request.files['face'].read(), np.uint8), cv2.IMREAD_COLOR)\n"
        << "        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)\n"
        << "        faces = face_cascade.detectMultiScale(gray, 1.1, 4)\n"
        << "        if len(faces) > 0:\n"
        << "            x, y, w, h = faces[0]\n"
        << "            face_crop = img[y:y+h, x:x+w]\n"
        << "            cv2.imwrite(f'{username}_ref.jpg', face_crop)\n"
        << "            return jsonify({'success': True})\n"
        << "    return jsonify({'success': False})\n\n"
        << "@app.route('/verify', methods=['POST'])\n"
        << "def verify():\n"
        << "    if 'face' in request.files:\n"
        << "        username = request.form.get('username', 'user')\n"
        << "        ref_path = f'{username}_ref.jpg'\n"
        << "        if not os.path.exists(ref_path): return jsonify({'verified': False})\n"
        << "        img_ref = cv2.imread(ref_path, 0)\n"
        << "        img_new = cv2.imdecode(np.frombuffer(request.files['face'].read(), np.uint8), cv2.IMREAD_GRAYSCALE)\n"
        << "        faces = face_cascade.detectMultiScale(img_new, 1.1, 4)\n"
        << "        if len(faces) > 0:\n"
        << "            x, y, w, h = faces[0]\n"
        << "            curr = cv2.resize(img_new[y:y+h, x:x+w], (img_ref.shape[1], img_ref.shape[0]))\n"
        << "            score = cv2.matchTemplate(curr, img_ref, cv2.TM_CCOEFF_NORMED).max()\n"
        << "            return jsonify({'verified': bool(score > 0.7)})\n"
        << "    return jsonify({'verified': False})\n\n"
        << "if __name__ == '__main__':\n"
        << "    app.run(host='127.0.0.1', port=5000)\n";
    file.close();
    return scriptPath;
}

bool ensureFaceServerRunning()
{
    if (isFaceServerReachable()) return true;

    const QString scriptPath = ensureFaceScript();
    if (scriptPath.isEmpty()) return false;

    if (!g_faceServerProcess) {
        g_faceServerProcess = new QProcess();
        g_faceServerProcess->setProcessChannelMode(QProcess::MergedChannels);
    }
    if (g_faceServerProcess->state() != QProcess::NotRunning) {
        // Déjà lancé ou en cours de démarrage, on checke juste la connexion
        if (isFaceServerReachable()) return true;
    }

    // Environnement "propre"
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.remove("PYTHONHOME");
    env.remove("PYTHONPATH");
    env.insert("PYTHONUTF8", "1");
    g_faceServerProcess->setProcessEnvironment(env);
    g_faceServerProcess->setWorkingDirectory(QCoreApplication::applicationDirPath());

    const QString pythonExe = QStandardPaths::findExecutable("python");
    const QString pyExe = QStandardPaths::findExecutable("py");

    QString selectedExe;
    QStringList selectedArgs;
    if (!pythonExe.isEmpty()) {
        selectedExe = pythonExe;
        selectedArgs = QStringList() << scriptPath;
    } else if (!pyExe.isEmpty()) {
        selectedExe = pyExe;
        selectedArgs = QStringList() << "-3" << scriptPath;
    }

    if (selectedExe.isEmpty()) {
        qWarning() << "FaceID: Aucun executable Python trouve (python ou py).";
        return false;
    }

    // --- CHECK DÉPENDANCES ---
    {
        QProcess depCheck;
        depCheck.setProcessEnvironment(env);
        QStringList checkArgs;
        if (selectedExe.contains("py.exe") || selectedExe.endsWith("/py")) checkArgs << "-3";
        checkArgs << "-c" << "import flask, cv2, numpy; print('ok')";
        
        depCheck.start(selectedExe, checkArgs);
        if (depCheck.waitForFinished(5000)) {
            QString out = QString::fromUtf8(depCheck.readAllStandardOutput()).trimmed();
            if (!out.contains("ok")) {
                qWarning() << "FaceID: Dependances manquantes (flask/opencv/numpy).";
                return false;
            }
        } else {
            depCheck.kill();
        }
    }

    // --- DÉMARRAGE SERVEUR ---
    g_faceServerProcess->start(selectedExe, selectedArgs);
    if (!g_faceServerProcess->waitForStarted(5000)) {
        qWarning() << "FaceID: Echec du lancement du process Python.";
        return false;
    }

    // Attendre que Flask soit prêt
    for (int i = 0; i < 15; ++i) {
        if (isFaceServerReachable()) return true;
        QThread::msleep(300);
    }

    qWarning() << "FaceID: Le serveur a demarre mais ne repond pas sur le port 5000.";
    return false;
}

bool envoyerMailServiceRh(const QString &destinataire,
                          const QString &sujet,
                          const QString &corps,
                          QString &erreur)
{
    MailSender sender;
    const QString smtpUser = QStringLiteral("rrayyyrrayyy@gmail.com");
    const QString smtpPass = QStringLiteral("qxel rihn nrrl fgtq");
    const QString expediteurService = QStringLiteral("Service RH - SmartResearchLab");
    const QString expediteurAdresseRh = QStringLiteral("rh@smartresearchlab.tn");
    return sender.envoyerMail(smtpUser, smtpPass, destinataire, sujet, corps, erreur,
                              expediteurService, expediteurAdresseRh);
}

bool verifierEmailParCode(const QString &email, QWidget *parent)
{
    const QString code = QString::number(QRandomGenerator::global()->bounded(100000, 1000000));
    QString err;
    const QString sujet = QStringLiteral("Code de verification - Recuperation mot de passe");
    const QString corps = QStringLiteral(
        "Bonjour,\n\n"
        "Une demande de reinitialisation de mot de passe a ete initiee pour votre compte employe.\n\n"
        "Code de verification : %1\n\n"
        "Si vous n'etes pas a l'origine de cette demande, contactez immediatement le service RH.\n"
    ).arg(code);

    if (!envoyerMailServiceRh(email, sujet, corps, err)) {
        QMessageBox::critical(parent, "Envoi impossible",
                              "Impossible d'envoyer le code de verification:\n" + err);
        return false;
    }

    for (int tentative = 1; tentative <= 3; ++tentative) {
        bool ok = false;
        const QString saisi = QInputDialog::getText(
                                  parent,
                                  "Verification email",
                                  QString("Entrez le code recu par email (tentative %1/3) :").arg(tentative),
                                  QLineEdit::Normal, "", &ok).trimmed();
        if (!ok) return false;
        if (saisi == code) return true;
    }

    QMessageBox::warning(parent, "Code incorrect",
                         "Verification email echouee apres 3 tentatives.");
    return false;
}

void notifierAdminsChangementMdp(const QString &username,
                                 const QString &nomComplet,
                                 const QString &emailEmploye,
                                 QWidget *parent)
{
    QSqlQuery adminsQuery;
    adminsQuery.prepare(
        "SELECT DISTINCT TRIM(EMAIL) "
        "FROM EMPLOYES "
        "WHERE EMAIL IS NOT NULL "
        "AND TRIM(EMAIL) <> '' "
        "AND UPPER(ROLE) IN ('ADMIN', 'RH', 'RESPONSABLE_LABOS')"
    );

    if (!adminsQuery.exec()) {
        qWarning() << "Notification admin impossible:" << adminsQuery.lastError().text();
        return;
    }

    QSet<QString> adminEmails;
    while (adminsQuery.next()) {
        const QString mail = adminsQuery.value(0).toString().trimmed();
        if (!mail.isEmpty()) adminEmails.insert(mail);
    }

    if (adminEmails.isEmpty()) {
        return;
    }

    const QString sujet = QStringLiteral("Alerte securite - Mot de passe employe modifie");
    const QString horodatage = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    const QString corps = QStringLiteral(
        "Notification automatique SmartResearch.\n\n"
        "Un employe a modifie son mot de passe via le parcours \"Mot de passe oublie\".\n\n"
        "Username : %1\n"
        "Nom      : %2\n"
        "Email    : %3\n"
        "Date/Heure : %4\n\n"
        "Si cette action est suspecte, veuillez verifier le compte immediatement."
    ).arg(username, nomComplet, emailEmploye, horodatage);

    QString err;
    bool atLeastOneSent = false;
    for (const QString &dest : std::as_const(adminEmails)) {
        if (envoyerMailServiceRh(dest, sujet, corps, err)) {
            atLeastOneSent = true;
        } else {
            qWarning() << "Echec notification admin" << dest << ":" << err;
        }
    }

    if (!atLeastOneSent) {
        QMessageBox::warning(parent, "Notification admin",
                             "Mot de passe mis a jour, mais l'alerte admin n'a pas pu etre envoyee.");
    }
}
} // namespace

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

    // Le serveur FaceID doit être prêt dès l'écran de login (avant MainWindow).
    if (!ensureFaceServerRunning()) {
        qWarning() << "FaceID: serveur IA non disponible au démarrage du login.";
    }
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
    if (!ensureFaceServerRunning()) {
        QMessageBox::critical(this, "Face ID indisponible",
                              "Le serveur FaceID n'a pas pu démarrer automatiquement.\n"
                              "Vérifiez Python + modules flask/opencv/numpy.");
        return;
    }

    QString user = ui->leUsername->text().trimmed();
    FaceAuth auth;

    if (user.isEmpty()) {
        // Mode autonome: on ne cherche que parmi les employés existants.
        QStringList employeeUsernames;
        QSqlQuery usersQuery;
        usersQuery.prepare("SELECT USERNAME FROM EMPLOYES WHERE USERNAME IS NOT NULL ORDER BY ID_EMPLOYE");

        if (!usersQuery.exec()) {
            QMessageBox::critical(this, "Erreur SQL", "Impossible de charger les comptes employés.");
            return;
        }

        while (usersQuery.next()) {
            const QString username = usersQuery.value(0).toString().trimmed();
            if (!username.isEmpty()) {
                employeeUsernames.append(username);
            }
        }

        if (employeeUsernames.isEmpty()) {
            QMessageBox::warning(this, "Face ID", "Aucun compte employé disponible pour l'authentification faciale.");
            return;
        }

        QString matchedUsername;
        if (auth.identifierUtilisateurParListe(employeeUsernames, &matchedUsername)) {
            QString errorMsg;
            if (Employe::authentifierFaceID(matchedUsername, &errorMsg)) {
                this->accept();
            } else {
                QMessageBox::critical(this, "Erreur SQL", errorMsg);
            }
        } else {
            QMessageBox::critical(this, "Échec IA", "Visage non reconnu parmi les employés.");
        }
        return;
    }

    if (auth.identifierUtilisateur(user)) {
        QString errorMsg;
        if (Employe::authentifierFaceID(user, &errorMsg)) {
            this->accept(); // Succès total !
        } else {
            QMessageBox::critical(this, "Erreur SQL", errorMsg);
        }
    } else {
        QMessageBox::critical(this, "Échec IA", "Visage non reconnu");
    }
}

void LoginDialog::on_Quitter_clicked()
{
    this->reject(); // Ferme la fenêtre proprement
}


void LoginDialog::on_btnForgotPass_clicked()
{
    bool ok = false;
    const QString username = QInputDialog::getText(
        this, "Recuperation securisee", "Nom d'utilisateur :", QLineEdit::Normal, "", &ok
    ).trimmed();
    if (!ok || username.isEmpty()) return;

    QSqlQuery profileQuery;
    profileQuery.prepare(
        "SELECT NOM, PRENOM, CIN, EMAIL, PASSWORD_HASH "
        "FROM EMPLOYES WHERE UPPER(TRIM(USERNAME)) = UPPER(TRIM(:user))"
    );
    profileQuery.bindValue(":user", username);
    if (!profileQuery.exec() || !profileQuery.next()) {
        QMessageBox::critical(this, "Acces refuse",
                              "Identite invalide. Verification impossible pour ce compte.");
        return;
    }

    const QString nom = profileQuery.value(0).toString().trimmed();
    const QString prenom = profileQuery.value(1).toString().trimmed();
    const QString cinBase = profileQuery.value(2).toString().trimmed();
    const QString emailBase = profileQuery.value(3).toString().trimmed();
    const QString ancienHash = profileQuery.value(4).toString().trimmed();
    const QString nomComplet = (nom + " " + prenom).trimmed();

    const QString cinSaisi = QInputDialog::getText(
        this, "Verification 1/3", "Numero CIN :", QLineEdit::Normal, "", &ok
    ).trimmed();
    if (!ok || cinSaisi.isEmpty()) return;

    const QString emailSaisi = QInputDialog::getText(
        this, "Verification 2/3", "Adresse email professionnelle :", QLineEdit::Normal, "", &ok
    ).trimmed();
    if (!ok || emailSaisi.isEmpty()) return;

    if (cinSaisi != cinBase || emailSaisi.compare(emailBase, Qt::CaseInsensitive) != 0) {
        QMessageBox::critical(this, "Acces refuse",
                              "Les informations de verification ne correspondent pas.");
        return;
    }

    if (!verifierEmailParCode(emailBase, this)) {
        return;
    }

    QString newPass;
    for (;;) {
        newPass = QInputDialog::getText(
                      this,
                      "Nouveau mot de passe",
                      "Entrez un mot de passe fort (min. 10 car., maj/min, chiffre, special) :",
                      QLineEdit::Password, "", &ok
                  );
        if (!ok || newPass.isEmpty()) return;

        if (!Employe::motDePasseAcceptable(newPass)) {
            QMessageBox::warning(this, "Mot de passe faible",
                                 "Le mot de passe doit atteindre au moins le niveau Fort.");
            continue;
        }

        const QString confirmation = QInputDialog::getText(
                                         this,
                                         "Confirmation",
                                         "Confirmez le nouveau mot de passe :",
                                         QLineEdit::Password, "", &ok
                                     );
        if (!ok) return;
        if (newPass != confirmation) {
            QMessageBox::warning(this, "Confirmation invalide",
                                 "Les deux mots de passe sont differents.");
            continue;
        }

        const QString newHash = QString(
            QCryptographicHash::hash(newPass.toUtf8(), QCryptographicHash::Sha256).toHex()
        );
        if (!ancienHash.isEmpty() && newHash == ancienHash) {
            QMessageBox::warning(this, "Mot de passe invalide",
                                 "Le nouveau mot de passe doit etre different de l'ancien.");
            continue;
        }
        break;
    }

    const QString newHash = QString(QCryptographicHash::hash(newPass.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE EMPLOYES SET PASSWORD_HASH = :pass WHERE UPPER(TRIM(USERNAME)) = UPPER(TRIM(:user))");
    updateQuery.bindValue(":pass", newHash);
    updateQuery.bindValue(":user", username);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Impossible de mettre a jour le mot de passe:\n" + updateQuery.lastError().text());
        return;
    }

    notifierAdminsChangementMdp(username, nomComplet, emailBase, this);
    QMessageBox::information(this, "Succes",
                             "Mot de passe mis a jour avec succes.\n"
                             "Une notification de securite a ete envoyee aux administrateurs.");
}
