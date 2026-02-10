#ifndef SMARTRESEARCHPUBLICATIONMANAGEMENT_H
#define SMARTRESEARCHPUBLICATIONMANAGEMENT_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class SmartResearchPublicationManagement; }
QT_END_NAMESPACE

class SmartResearchPublicationManagement : public QMainWindow
{
    Q_OBJECT

public:
    SmartResearchPublicationManagement(QWidget *parent = nullptr);
    ~SmartResearchPublicationManagement();

private slots:
    // --- Système ---
    void on_btnLoginSubmit_clicked(); // Déclaré UNE SEULE FOIS ici
    void on_BtnTheme_clicked();

    // --- Navigation Principale (Menu Gauche) ---
    void on_BtnEmployee_clicked();
    void on_BtnFinance_clicked();
    void on_BtnPublication_clicked();
    void on_BtnLabs_clicked();
    void on_BtnInventory_clicked();
    void on_BtnPlans_clicked();

    // --- Logique Finance ---
    void on_BtnAdd_clicked();
    void on_BtnEdit_clicked();
    void on_BtnPopupCancelFinance_clicked();
    void on_BtnPopupSaveFinance_clicked();

    // --- Logique Gestion Employés ---
    void on_BtnEmployee_2_clicked();
    void on_ADD_user_2_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_34_clicked(); // Retour détails
    void on_pushButton_35_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_39_clicked(); // Save update
    void on_pushButton_40_clicked();
    void on_Cancel_2_clicked();      // Annuler ajout
    void on_Update_R_2_clicked();    // Confirmer ajout
    void on_btnCancelUpdate_clicked();

    void on_btnLogin_clicked();

    void on_BtnLogout_clicked();


    void on_pushButton_clicked();

    void on_Quitter_clicked();

private:
    Ui::SmartResearchPublicationManagement *ui;
    bool m_dark = false;

    // Fonctions utilitaires (Méthodes, pas des slots)
    void applyTheme(const QString& qssPath);
    void goToUpdatePage();
    void returnToList();
};

#endif // SMARTRESEARCHPUBLICATIONMANAGEMENT_H
