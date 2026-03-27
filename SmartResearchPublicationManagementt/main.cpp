#include "mainwindow.h"
#include "logindialog.h"
#include "connection.h"
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
    QString themeFile = darkMode ? ":/theme/style.qss" : ":/theme/style_light.qss";
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

    // 2) Boucle de cycle de vie (Login <-> MainWindow)
    bool restart = true;
    while (restart) {
        restart = false;
        
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            // Si l'utilisateur annule ou ferme la fenêtre de login
            break;
        }

        // 3) Ouverture de la fenêtre principale
        // On n'instancie MainWindow qu'après la réussite du login pour économiser les ressources
        MainWindow w;
        
        // Connecter le signal de déconnexion pour demander le redémarrage (Login)
        QObject::connect(&w, &MainWindow::logoutRequested, [&restart]() {
            restart = true;
        });

        w.show();

        // Boucle d'événements principale pour la fenêtre MainWindow
        a.exec(); 
    }

    // 4) Nettoyage avant fermeture
    c->closeConnection();

    return 0;
}
