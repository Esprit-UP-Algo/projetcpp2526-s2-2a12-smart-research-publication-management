#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAjouter_clicked();

    void on_btnRetour_clicked();

    void on_btnRetour_2_clicked();

    void on_btnmodifier_clicked();

    void on_btnMode_clicked();
    void on_btnMode_2_clicked();
    void on_btnMode_3_clicked();

private:
    Ui::MainWindow *ui;
private:
    bool darkMode = false;
    void applyDarkMode();
    void applyLightMode();

};
#endif // MAINWINDOW_H
