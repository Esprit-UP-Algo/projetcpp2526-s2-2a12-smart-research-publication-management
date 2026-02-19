#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QString>


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
// //////////////////////////////////////////////////////////////////////////////////////////////////// //
    // ===== FINANCE (Hichem) =====
    void initFinanceUi();      // init combos + table + load
    void setupTableFinance();
    void loadFinance();
    void showFinanceList();

    QString idFinanceToEdit;   // IDFINANCE de la ligne sélectionnée (pour UPDATE)
    QString idFinanceToDelete; // IDFINANCE de la ligne sélectionnée (pour DELETE)
// ///////////////////////////////////////////////////////////////////////////////////////////////// //

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
    void on_btnVoirStatistiquesPub_2_clicked();
    void on_btnAjouterPub_2_clicked();
    void on_btnModifierPub_2_clicked();
    void on_btnAjouterPub_3_clicked();
    void on_btnAjouterPub_4_clicked();
    void on_BtnPopupCancelLabs_5_clicked();
    void on_BtnPopupCancelLabs_3_clicked();
    void on_retour_stat_2_clicked();
    void on_retour_stat_3_clicked();
    void on_retour_stat_8_clicked();
    void on_BtnInventoryAdd_clicked();
    void on_BtnInventoryAdd_2_clicked();
    void on_BtnInventoryEdit_clicked();
    void on_BtnInventoryAdd_5_clicked();
    void on_retour_stat_7_clicked();
    void on_BtnPopupCancelInventory_2_triggered(QAction *arg1);
    void on_BtnPopupCancelInventory_2_clicked();
    void on_BtnPopupCancelInventory_clicked();
    void on_retour_stat_6_clicked();
    void on_retour_stat_4_clicked();
    void on_BtnPopupCancelFinance_2_clicked();
    void on_BtnPopupCancelFinance_clicked();
    void on_retour_stat_5_clicked();
    void on_BtnAdd_clicked();
    void on_BtnEdit_clicked();
    void on_BtnAdd_3_clicked();
    void on_BtnAdd_4_clicked();
    void on_BtnPopupCancelLabs_6_clicked();
    void on_btnCancelEditEmp_clicked();
    void on_BtnPopupCancelLabs_10_clicked();
    void on_BtnPopupCancelLabs_9_clicked();
    void on_BtnPopupCancelLabs_7_clicked();
    void on_BtnPopupCancelLabs_8_clicked();
    void on_btnSaveEmployee_2_clicked();
    void on_btnFinance_clicked();
    void on_BtnPopupSaveFinance_2_clicked();
    void on_BtnDelete_clicked();
    void on_BtnPopupSaveFinance_clicked();
    void on_BtnApply_clicked();
    void on_BtnReset_clicked();
    void on_BtnExport_clicked();
};

#endif
