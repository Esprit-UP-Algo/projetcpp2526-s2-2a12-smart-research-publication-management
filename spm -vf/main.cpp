#include "mainwindow.h"
#include "logindialog.h"
#include "connection.h"
#include "arduino.h"
#include "rfidhandler.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QSettings>

int main(int argc, char *argv[])
{
    // Configuration de l'application
    QApplication a(argc, argv);

    // Charger le thème QSS selon la préférence sauvegardée
    QSettings settings("SmartResearchLab", "Theme");
    bool darkMode = settings.value("darkMode", false).toBool();
    QString themeFile = darkMode ? ":/theme/style_dark.qss" : ":/theme/style_light.qss";
    QFile styleFile(themeFile);
    if(styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
    }

    // 1) Connexion à la Base de Données (Singleton)
    Connection* c = Connection::instance();
    if (!c->createConnect()) {
        QMessageBox::critical(nullptr, "Erreur Fatale",
                              "Impossible d'établir une connexion avec la base de données.\n"
                              "Vérifiez vos paramètres réseau ou SQL.");
        return -1;
    }

    // 2) Arduino + RfidHandler — actifs AVANT le login, pendant toute la session
    Arduino arduino;
    int retArduino = arduino.connect_arduino();
    switch (retArduino) {
    case  0: qDebug() << "[Arduino] Connecté sur" << arduino.getarduino_port_name(); break;
    case  1: qDebug() << "[Arduino] Trouvé mais port occupé —" << arduino.getarduino_port_name(); break;
    case -1: qDebug() << "[Arduino] Non détecté — pointage RFID désactivé"; break;
    }
    // RfidHandler traite les cartes dès maintenant, même sans utilisateur connecté
    RfidHandler rfidHandler(&arduino);

    // 3) Boucle de cycle de vie (Login <-> MainWindow)
    bool restart = true;
    while (restart) {
        restart = false;

        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            break;
        }

        // 4) Ouverture de la fenêtre principale
        MainWindow w(&arduino);

        // Quand un pointage RFID se produit, rafraîchir le tableau employés dans l'UI
        QObject::connect(&rfidHandler, &RfidHandler::pointageEffectue,
                         &w, &MainWindow::onPointageRfid);
        
        // Connecter le signal de déconnexion pour demander le redémarrage (Login)
        QObject::connect(&w, &MainWindow::logoutRequested, [&restart]() {
            restart = true;
        });
        w.notifierConnexion();
        w.show();

        // Boucle d'événements principale pour la fenêtre MainWindow
        a.exec(); 
    }

    // 4) Nettoyage avant fermeture
    c->closeConnection();

    return 0;
}
