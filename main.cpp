#include "login.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Charger le style depuis les ressources
    QFile styleFile(":/style/style.qss");  // ← chemin spécial Qt (dans .qrc)
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = QLatin1String(styleFile.readAll());
        a.setStyleSheet(style);
        qDebug() << "STYLE CHARGÉ DEPUIS RESSOURCES !";
        styleFile.close();
    } else {
        qDebug() << "ERREUR : style.qss non trouvé dans les ressources";
    }

    Login login;
    login.show();

    return a.exec();
}
