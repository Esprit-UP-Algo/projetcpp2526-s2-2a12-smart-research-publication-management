#include "gestion_de_stock.h"
#include "ui_gestion_de_stock.h"

gestion_de_stock::gestion_de_stock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_de_stock)
{
    ui->setupUi(this);
}

gestion_de_stock::~gestion_de_stock()
{
    delete ui;
}
