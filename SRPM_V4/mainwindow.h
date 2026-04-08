#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QString>
#include "finance.h"
#include "ocrscanner.h"
#include "publication.h"
#include "labs.h"
#include "employe.h"
#include "inventory.h"
#include "projet.h"
#include <QSqlTableModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void notifierConnexion(); // Pour signaler l'entrée de l'utilisateur

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model; // <--- C'est ce type qu'il faut utiliser
    QString currentUser;
    QNetworkAccessManager *networkManager;
    QString m_tempFaceEncoding; // Pour stocker la signature

    // ===== FINANCE =====
    Finance::Row selectedFinanceRowFromTable(bool *ok=nullptr) const;
    bool exportInternalInvoicePdf_19(const QString& filePath, const Finance::Row& row);
    void initFinanceUi();
    void setupTableFinance();
    void loadFinance();
    void showFinanceList();
    void updateFinanceStats();
    void openCurrencyConverter();
    QString selectedFinanceId() const;
    QString idFinanceToEdit;   // seulement pour UPDATE

    // ===== PUBLICATION ===================================================

    void initPublicationUi();
    void loadPublications();
    QString selectedPublicationId() const;

    QString idPublicationToEdit;

    void clearLayout(QLayout *layout);
    void showPublicationStats();
    void showPublicationStatsByDomaine();
    void showPublicationStatsByStatut();

    QString genererReponsePublication(const QString &question);
    QString formaterResultatsPublication(QSqlQuery &query);
    QString genererContenuMailPublications();
    bool emailValide(const QString &email);

    // ===== LABS ===========================================================
    void verrouillerChampsAffichage();
    void initLabsUi();
    void setupTableLabs();
    void loadLabs();
    QString selectedLabsId() const;
    QString idLabsToEdit;
    void showLabsPaymentStats();

    // ===== EMPLOYEE =====
    void initEmployeUserGuidance();
    void loadEmployees();
    QString m_emailEmployeEditOriginal;
    QString ancienCin;
    QString ancienUsername;
    int indexSelectionne = -1;
    void filterEmployees(const QString &searchText);
    void sortByEmbaucheDate();
    bool embaucheAscending = true;
    void configurerPermissions();
    void on_btn_reset_clicked();
    QMenu *menuNotif;     // Le menu qui va descendre du bouton
    int nbNotifs = 0;     // Le compteur (ex: 1, 2, 3...)

    void ajouterNotification(const QString &titre, const QString &message);
    // ====================

    // ===== PROJECTS =====
    void initProjetsUi();
    void loadProjets();
    void showProjetsStats();
    QString selectedProjetId() const;
    QString idProjetToEdit;

    // ===== INVENTORY =====
    void initInventoryUi();
    void setupTableInventory();
    void loadInventory();
    QString selectedInventoryIdProduct() const;
    QString selectedInventorySku() const;
    QString idProductToEdit;
    QString skuToEdit;
    bool syncInventoryReservationsFromLabs(QString *err = nullptr);
    // =====================

    void updateTopTitle(int index);
    void applyModernStyle();
    void setActiveButton(QPushButton *btn);
    void toggleTheme();
    void updateThemeButton();

    bool m_isDarkTheme = false;

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
    void on_btn_exportt_clicked();      // Le slot pour ton bouton Export Excel
    void simulerPointage();
    void on_btnStat_emp_clicked();
    void on_btn_ret_clicked();

    // Publication slots
    void on_btnAjouterPub_clicked();
    void on_btnAjouterPub_2_clicked();
    void on_btnAjouterPub_3_clicked();
    void on_btnAjouterPub_4_clicked();
    void on_btnAjouterPub_5_clicked();
    void on_btnmapl_3_clicked();
    void on_btnAppliquerPub_clicked();
    void on_btnRetourAddPub_clicked();
    void on_btnRetourEditPub_clicked();
    void on_btnModifierPub_clicked();
    void on_btnModifierPub_2_clicked();
    void on_btnVoirStatistiquesPub_2_clicked();
    void on_retour_stat_clicked();
    void on_retour_stat_2_clicked();
    void on_retour_stat_3_clicked();
    void on_retour_stat_4_clicked();
    void on_retour_stat_5_clicked();
    void on_retour_stat_6_clicked();
    void on_retour_stat_7_clicked();
    void on_retour_stat_8_clicked();
    void on_retour_stat_9_clicked();
    void on_retour_statn_clicked();
    void on_btnSupprimerPub_clicked();
    void on_btnAddPub_clicked();
    void on_btnConfirmEditPub_clicked();
    void on_btnExporterPub_clicked();
    void on_lineSearchPub_textChanged(const QString &text);
    void on_comboTriPub_currentIndexChanged(int index);
    void on_btnVoirStatistiquesPub_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_btnChatbotPub_clicked();
    void on_btnRetourChatbotPub_clicked();
    void on_btnEnvoyerQuestionPub_clicked();
    void on_btnMailingPub_clicked();


    // Labs slots
    void on_btnOpenGoogleMaps_clicked();
    // Nouveaux slots pour le filtrage dynamique
    void filterLabsDynamic();
    void resetLabsFilters();
    void on_pointage_pressed();

    void on_btnScanFace_clicked();

protected:
    // Le filtre pour capturer le double-clic sur aff2
    bool eventFilter(QObject *obj, QEvent *event) override;
    void on_btnPasteLocation_clicked();
    void onMapLocationSelected(const QString& title);
    void on_BtnExportLabs_clicked(); // Remplacez par le vrai nom de votre bouton PDF
    void on_BtnPopupCancelLabs_3_clicked();
    void on_BtnPopupCancelLabs_5_clicked();
    void on_BtnPopupCancelLabs_6_clicked();
    void on_BtnPopupCancelLabs_7_clicked();
    void on_BtnPopupCancelLabs_8_clicked();
    void on_BtnPopupCancelLabs_9_clicked();
    void on_BtnPopupCancelLabs_10_clicked();
    void on_TableLabs_2_headerClicked(int logicalIndex);
    void on_BtnPopupSaveLabs_3_clicked();   // ajouter
    void on_BtnPopupResetLabs_3_clicked();
    void on_BtnPopupSaveLabs_5_clicked();   // modifier
    void on_BtnPopupResetLabs_5_clicked();
    void on_btnSupprimerPub_2_clicked();    // supprimer labs
    void on_btnAppliquerPub_3_clicked();    // filtre
    void on_btnReinitialiserPub_3_clicked();// reset filtre
    void on_BtnExportLabsDirect_clicked();
    // Inventory slots
    void handleInventoryAdd();
    void handleInventoryView();
    void handleInventoryEdit();
    void handleInventoryStats();
    void handleInventoryDelete();
    void handleInventoryExportPdf();
    void handleInventoryDetailExportPdf();

    void on_BtnPopupCancelInventory_2_triggered(QAction *arg1);
    void on_BtnPopupCancelInventory_2_clicked();
    void on_BtnPopupCancelInventory_clicked();
    void on_BtnPopupSaveInventory_clicked();    // ADD save
    void on_BtnPopupResetInventory_clicked();   // ADD reset
    void on_BtnPopupSaveInventory_2_clicked();  // EDIT save
    void on_BtnPopupResetInventory_2_clicked(); // EDIT reset
    void fillTableInventoryRow(int row, const Inventory::Row &data);
    void applyInventoryFilter();               // filter/search (manual connect)
    void refreshInventoryTypeFilter();         // DISTINCT TYPE depuis la BD
    void resetInventoryFilters();              // recherche vierge + tous + tri SKU

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
    void on_BtnOcrReceipt_clicked();

    // Projects slots
    void on_btnRetourEditProj_clicked();
    void on_btnRetourAddProj_clicked();
    void on_btnAjouterProj_clicked();
    void on_btnModifierProj_clicked();
    void on_btnVoirStatistiquesProj_clicked();
    void on_btnAddProj_clicked();
    void on_btnConfirmEditProj_clicked();
    void on_btnSupprimerProj_clicked();
    void on_btnAppliquerProj_clicked();
    void on_btnFiltrerDateProj_clicked();
    void on_btnAnnuler_emp_clicked();
    void on_btnForm_emp_clicked();
    void on_pushButton_clicked();
    void on_pointage_clicked();
    void on_btn_ret_triggered(QAction *arg1);
    void on_BtnPopupCancelLabs_6_triggered(QAction *arg1);

signals:
    void logoutRequested();
};

#endif
