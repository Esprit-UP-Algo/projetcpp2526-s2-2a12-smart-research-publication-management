#ifndef GESTION_DE_STOCK_H
#define GESTION_DE_STOCK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class gestion_de_stock;
}
QT_END_NAMESPACE

class gestion_de_stock : public QMainWindow
{
    Q_OBJECT

public:
    gestion_de_stock(QWidget *parent = nullptr);
    ~gestion_de_stock();

private:
    Ui::gestion_de_stock *ui;
};
#endif // GESTION_DE_STOCK_H
