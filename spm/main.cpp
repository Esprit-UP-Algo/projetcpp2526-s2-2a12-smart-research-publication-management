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

    // 2) Arduino RFID (carte 1) + Arduino Keypad (carte 2)
    Arduino arduinoRfid;
    int retRfid = arduinoRfid.connect_arduino();
    switch (retRfid) {
    case  0: qDebug() << "[Arduino RFID] Connecté sur" << arduinoRfid.getarduino_port_name(); break;
    case  1: qDebug() << "[Arduino RFID] Port occupé —" << arduinoRfid.getarduino_port_name(); break;
    case -1: qDebug() << "[Arduino RFID] Non détecté"; break;
    }

    Arduino arduinoKeypad;
    int retKeypad = arduinoKeypad.connect_arduino(arduinoRfid.getarduino_port_name());
    switch (retKeypad) {
    case  0: qDebug() << "[Arduino Keypad] Connecté sur" << arduinoKeypad.getarduino_port_name(); break;
    case  1: qDebug() << "[Arduino Keypad] Port occupé —" << arduinoKeypad.getarduino_port_name(); break;
    case -1: qDebug() << "[Arduino Keypad] Non détecté"; break;
    }

    // RfidHandler : écoute l'Arduino RFID + attache le Keypad
    RfidHandler rfidHandler(&arduinoRfid);
    rfidHandler.attachKeypad(&arduinoKeypad);

    // 3) Boucle de cycle de vie (Login <-> MainWindow)
    bool restart = true;
    while (restart) {
        restart = false;

        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            break;
        }

        // 4) Ouverture de la fenêtre principale
        // MainWindow reçoit l'Arduino Keypad pour écrire MOTOR/SKU_OK/QTY
        MainWindow w(&arduinoKeypad);

        // Quand un pointage RFID se produit, rafraîchir le tableau employés dans l'UI
        QObject::connect(&rfidHandler, &RfidHandler::pointageEffectue,
                         &w, &MainWindow::onPointageRfid);

        // Keypad : SKU scanné → vérification inventaire + moteur
        QObject::connect(&rfidHandler, &RfidHandler::skuRecu,
                         &w, &MainWindow::traiter_sku);
        // Keypad : saisie en cours → aperçu dans la barre de recherche
        QObject::connect(&rfidHandler, &RfidHandler::inputSkuRecu,
                         &w, &MainWindow::afficher_input_sku);
        
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
