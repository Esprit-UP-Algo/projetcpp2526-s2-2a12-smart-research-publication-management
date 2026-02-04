#include "gestion_de_stock.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly))
    {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    gestion_de_stock w;
    w.show();

    return a.exec();
}
