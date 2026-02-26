#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QString>
#include "finance.h"
#include "publication.h"
#include "labs.h"
#include "employe.h"
#include "inventory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     int empId() const { return m_empId; }
        explicit MainWindow(int empId, QWidget *parent = nullptr);
private:
    Ui::MainWindow *ui;
        int m_empId = -1;


    // ===== FINANCE =====
    Finance::Row selectedFinanceRowFromTable(bool *ok=nullptr) const;
    bool exportInternalInvoicePdf_19(const QString& filePath, const Finance::Row& row);
    void initFinanceUi();
    void setupTableFinance();
    void loadFinance();
    void showFinanceList();
    QString selectedFinanceId() const;
    QString idFinanceToEdit;   // seulement pour UPDATE
    // ====================

    // ===== PUBLICATION =====
    void initPublicationUi();
    void loadPublications();
    QString selectedPublicationId() const;
    QString idPublicationToEdit;

    // =======================

    // ===== LABS =====
    void initLabsUi();
    void setupTableLabs();
    void loadLabs();
    QString selectedLabsId() const;
    QString idLabsToEdit;
    // ================

    // ===== EMPLOYEE =====
    void loadEmployees();
    QString ancienCin;
    QString ancienUsername;
    int indexSelectionne = -1;
    void filterEmployees(const QString &searchText);
    void sortByEmbaucheDate();
    bool embaucheAscending = true;
    // ====================

    // ===== INVENTORY =====
    void initInventoryUi();
    void setupTableInventory();
    void loadInventory();
    QString selectedInventoryIdProduct() const;
    QString selectedInventorySku() const;
    QString idProductToEdit;
    QString skuToEdit;
    // =====================

    void updateTopTitle(int index);
    void applyModernStyle();
    void setActiveButton(QPushButton *btn);

private slots:
    // Navigation
    void goEmployee();
    void goInventaire();
    void goPublication();
    void goFinance();
    void goLaboratoires();
    void goProjets();
    void onDeconnecter();

    // Employee slots
    void on_btnAjouterEmp_clicked();
    void on_btnModifier_emp_clicked();
    void on_btnSaveEditEmployee_clicked();
    void on_tableEmployees_clicked(const QModelIndex &index);
    void on_btnSaveEmployee_clicked();
    void on_btnSaveEmployee_2_clicked();
    void on_btnSupprimer_emp_clicked();
    void on_btnTrier_emp_3_clicked();
    void on_btnConge_emp_3_clicked();
    void on_btnConge_emp_clicked();
    void on_btnConge_emp_2_clicked();
    void on_btnChercher_emp_clicked();
    void on_btnExporter_emp_excel_3_clicked();
    void on_btnTrier_emp_clicked();
    void on_btnCancelEditEmp_clicked();

    // Publication slots
    void on_btnAjouterPub_clicked();
    void on_btnAjouterPub_2_clicked();
    void on_btnAjouterPub_3_clicked();
    void on_btnAjouterPub_4_clicked();
    void on_btnRetourAddPub_clicked();
    void on_btnRetourEditPub_clicked();
    void on_btnModifierPub_clicked();
    void on_btnModifierPub_2_clicked();
    void on_btnVoirStatistiquesPub_clicked();
    void on_btnVoirStatistiquesPub_2_clicked();
    void on_retour_stat_clicked();
    void on_retour_stat_2_clicked();
    void on_retour_stat_3_clicked();
    void on_retour_stat_4_clicked();
    void on_retour_stat_5_clicked();
    void on_retour_stat_6_clicked();
    void on_retour_stat_7_clicked();
    void on_retour_stat_8_clicked();
    void on_retour_statn_clicked();
    void on_btnSupprimerPub_clicked();
    void on_btnAddPub_clicked();
    void on_btnConfirmEditPub_clicked();

    // Labs slots
    void on_BtnPopupCancelLabs_3_clicked();
    void on_BtnPopupCancelLabs_5_clicked();
    void on_BtnPopupCancelLabs_6_clicked();
    void on_BtnPopupCancelLabs_7_clicked();
    void on_BtnPopupCancelLabs_8_clicked();
    void on_BtnPopupCancelLabs_9_clicked();
    void on_BtnPopupCancelLabs_10_clicked();
    void on_BtnPopupSaveLabs_3_clicked();   // ajouter
    void on_BtnPopupResetLabs_3_clicked();
    void on_BtnPopupSaveLabs_5_clicked();   // modifier
    void on_BtnPopupResetLabs_5_clicked();
    void on_btnSupprimerPub_2_clicked();    // supprimer labs
    void on_btnAppliquerPub_3_clicked();    // filtre
    void on_btnReinitialiserPub_3_clicked();// reset filtre

    // Inventory slots
    void on_BtnInventoryAdd_clicked();
    void on_BtnInventoryAdd_2_clicked();
    void on_BtnInventoryEdit_clicked();
    void on_BtnInventoryAdd_5_clicked();
    void on_BtnPopupCancelInventory_2_triggered(QAction *arg1);
    void on_BtnPopupCancelInventory_2_clicked();
    void on_BtnPopupCancelInventory_clicked();
    void on_BtnPopupSaveInventory_clicked();    // ADD save
    void on_BtnPopupResetInventory_clicked();   // ADD reset
    void on_BtnPopupSaveInventory_2_clicked();  // EDIT save
    void on_BtnPopupResetInventory_2_clicked(); // EDIT reset
    void on_BtnInventoryDelete_clicked();       // DELETE
    void on_BtnInventoryApply_clicked();        // filter/search

    // Finance slots
    void on_btnFinance_clicked();
    void on_BtnPopupCancelFinance_2_clicked();
    void on_BtnPopupCancelFinance_clicked();
    void on_BtnPopupSaveFinance_2_clicked();
    void on_BtnPopupSaveFinance_clicked();
    void on_BtnAdd_clicked();
    void on_BtnAdd_3_clicked();
    void on_BtnAdd_4_clicked();
    void on_BtnEdit_clicked();
    void on_BtnDelete_clicked();
    void on_BtnApply_clicked();
    void on_BtnReset_clicked();
    void on_BtnExport_clicked();

    // Projects slots
    void on_btnRetourEditProj_clicked();
    void on_btnRetourAddProj_clicked();
    void on_btnAjouterProj_clicked();
    void on_btnModifierProj_clicked();
    void on_btnVoirStatistiquesProj_clicked();
    void on_btnAnnuler_emp_clicked();
    void on_btnForm_emp_clicked();
    void on_btnAddProj_clicked();
};

#endif
