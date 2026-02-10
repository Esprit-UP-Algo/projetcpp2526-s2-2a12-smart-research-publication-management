#include "smartresearchpublicationmanagement.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SmartResearchPublicationManagement w;
    w.show();

    return a.exec();
}
