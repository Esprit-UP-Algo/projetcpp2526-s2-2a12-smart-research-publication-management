#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void updateTopTitle(int index);

    void applyModernStyle();
    void setActiveButton(QPushButton *btn);

private slots:
    void goEmployee();
    void goInventaire();
    void goPublication();
    void goFinance();
    void goLaboratoires();
    void goProjets();
    void onDeconnecter();
    void on_btnAjouterPub_clicked();
    void on_btnRetourAddPub_clicked();
    void on_btnRetourEditPub_clicked();
    void on_btnModifierPub_clicked();
    void on_btnVoirStatistiquesPub_clicked();
    void on_retour_stat_clicked();
    void on_btnSupprimerPub_clicked();

    void on_btnAjouterEmp_clicked();
    void on_btnTrier_emp_3_clicked();
    void on_btnConge_emp_3_clicked();
    void on_btnConge_emp_clicked();
    void on_btnConge_emp_2_clicked();
    void on_btnChercher_emp_clicked();
    void on_btnExporter_emp_excel_3_clicked();
    void on_btnTrier_emp_clicked();
};

#endif
