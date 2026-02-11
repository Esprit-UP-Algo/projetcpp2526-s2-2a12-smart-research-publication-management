#include "smartresearchpublicationmanagement.h"
#include "ui_smartresearchpublicationmanagement.h"
#include <QFile>
#include <QDate>
#include <QDebug>

SmartResearchPublicationManagement::SmartResearchPublicationManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartResearchPublicationManagement)
{
    ui->setupUi(this);

    // Initialisation Thème
    applyTheme(":/styles/light.qss");

    // 1. DÉMARRAGE : Afficher la page Login (Index 1 selon votre code)
    ui->Pages->setCurrentIndex(2);

    // 3. INITIALISATION DES AUTRES STACKS
    if(ui->EmployeeStack) ui->EmployeeStack->setCurrentIndex(0);
    if(ui->FinanceStack) ui->FinanceStack->setCurrentIndex(0);
    // Remplissage des ComboBox Finance
    ui->FormType->addItems({"Dépense","Revenu"});
    ui->FormCategory->addItems({"Matériel","Service","Transport","Autre"});
    ui->FormPayMode->addItems({"Cash","Carte","Virement","Chèque"});
}



SmartResearchPublicationManagement::~SmartResearchPublicationManagement()
{
    delete ui;
}

// --- Système de Thème ---
void SmartResearchPublicationManagement::applyTheme(const QString& qssPath)
{
    QFile f(qssPath);
    if (f.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(QString::fromUtf8(f.readAll()));
        f.close();
    }
}

void SmartResearchPublicationManagement::on_BtnTheme_clicked()
{
    m_dark = !m_dark;
    applyTheme(m_dark ? QString(":/styles/dark.qss") : QString(":/styles/light.qss"));
}

// --- Navigation Menu Principal ---
void SmartResearchPublicationManagement::on_BtnEmployee_clicked(){ ui->Pages->setCurrentWidget(ui->PageEmployee); }
void SmartResearchPublicationManagement::on_BtnFinance_clicked(){ ui->Pages->setCurrentWidget(ui->PageFinance); }
void SmartResearchPublicationManagement::on_BtnPublication_clicked(){ ui->Pages->setCurrentWidget(ui->PagePublication); }
void SmartResearchPublicationManagement::on_BtnLabs_clicked(){ ui->Pages->setCurrentWidget(ui->PageLabs); }
void SmartResearchPublicationManagement::on_BtnInventory_clicked(){ ui->Pages->setCurrentWidget(ui->PageInventory); }
void SmartResearchPublicationManagement::on_BtnPlans_clicked(){ ui->Pages->setCurrentWidget(ui->PagePlans); }

// --- Gestion Finance ---
void SmartResearchPublicationManagement::on_BtnAdd_clicked()
{
    ui->FinanceStack->setCurrentIndex(1);
    ui->PopupTitleFinance->setText("Ajouter une transaction");
    ui->FormCode->clear();
    ui->FormAmount->clear();
    ui->FormDate->setDate(QDate::currentDate());
}

void SmartResearchPublicationManagement::on_BtnEdit_clicked()
{
    ui->FinanceStack->setCurrentIndex(1);
    ui->PopupTitleFinance->setText("Modifier la transaction");
}

void SmartResearchPublicationManagement::on_BtnPopupCancelFinance_clicked() { ui->FinanceStack->setCurrentIndex(0); }

void SmartResearchPublicationManagement::on_BtnPopupSaveFinance_clicked()
{
    ui->FinanceStack->setCurrentIndex(0);
    QMessageBox::information(this, "OK", "Transaction enregistrée.");
}

// --- Gestion Employés (Anciennement dans usermang.cpp) ---
void SmartResearchPublicationManagement::on_BtnEmployee_2_clicked() { returnToList(); }

void SmartResearchPublicationManagement::on_ADD_user_2_clicked() { ui->EmployeeStack->setCurrentIndex(2); }

void SmartResearchPublicationManagement::on_pushButton_13_clicked() // Modifier
{
    if (ui->tableWidget_2->currentRow() < 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé.");
        return;
    }
    goToUpdatePage();
}

void SmartResearchPublicationManagement::on_pushButton_14_clicked() // Détails
{
    if (ui->tableWidget_2->currentRow() < 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé.");
        return;
    }
    ui->EmployeeStack->setCurrentIndex(3);
}

void SmartResearchPublicationManagement::on_pushButton_15_clicked() // Supprimer
{
    if (ui->tableWidget_2->currentRow() >= 0) {
        if (QMessageBox::question(this, "Confirmation", "Supprimer ?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
            ui->tableWidget_2->removeRow(ui->tableWidget_2->currentRow());
        }
    }
}

void SmartResearchPublicationManagement::on_pushButton_39_clicked() // Save update
{
    QMessageBox::information(this, "OK", "Modifications enregistrées.");
    returnToList();
}

void SmartResearchPublicationManagement::on_Update_R_2_clicked() // Confirmer Ajout
{
    QMessageBox::information(this, "OK", "Employé ajouté.");
    returnToList();
}

// Fonctions de retour/navigation interne employé
void SmartResearchPublicationManagement::on_pushButton_34_clicked() { returnToList(); }
void SmartResearchPublicationManagement::on_Cancel_2_clicked() { returnToList(); }

void SmartResearchPublicationManagement::goToUpdatePage() { ui->EmployeeStack->setCurrentIndex(1); }
void SmartResearchPublicationManagement::returnToList() { ui->EmployeeStack->setCurrentIndex(0); }



void SmartResearchPublicationManagement::on_pushButton_35_clicked()
{
    QMessageBox::information(this, "Simulation", "Employé ajouté.");
    returnToList();
}


void SmartResearchPublicationManagement::on_pushButton_40_clicked()
{
    returnToList();
}


void SmartResearchPublicationManagement::on_btnCancelUpdate_clicked()
{
    returnToList();

}




void SmartResearchPublicationManagement::on_BtnLogout_clicked()
{

}



void SmartResearchPublicationManagement::on_Quitter_clicked()
{
    // On demande confirmation avant de fermer l'application
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quitter", "Êtes-vous sûr de vouloir fermer l'application ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Ferme la fenêtre principale et arrête le programme
        this->close();
    }
}




void SmartResearchPublicationManagement::on_btnAjouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void SmartResearchPublicationManagement::on_btnRetour_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SmartResearchPublicationManagement::on_btnAjouter_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SmartResearchPublicationManagement::on_btnmodifier_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void SmartResearchPublicationManagement::on_btnRetour_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SmartResearchPublicationManagement::on_btnAjouter_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void SmartResearchPublicationManagement::on_BtnLabAdd_2_clicked()
{
    ui->stackedlab->setCurrentIndex(1);
}


void SmartResearchPublicationManagement::on_BtnLabEdit_2_clicked()
{
    ui->stackedlab->setCurrentIndex(2);
}


void SmartResearchPublicationManagement::on_annuleL_clicked()
{
    ui->stackedlab->setCurrentIndex(0);

}


void SmartResearchPublicationManagement::on_pushButton_5_clicked()
{
    ui->stackedlab->setCurrentIndex(0);
}


void SmartResearchPublicationManagement::on_BtnInventoryAdd_clicked()
{
    ui->InventoryStack->setCurrentIndex(2);
}


void SmartResearchPublicationManagement::on_BtnInventoryEdit_clicked()
{
    ui->InventoryStack->setCurrentIndex(1);

}


void SmartResearchPublicationManagement::on_BtnPopupCancelInventory_3_clicked()
{
    ui->InventoryStack->setCurrentIndex(0);
}


void SmartResearchPublicationManagement::on_BtnPopupCancelInventory_2_clicked()
{
    ui->InventoryStack->setCurrentIndex(0);

}

void SmartResearchPublicationManagement::on_BtnPopupCancelInventory_4_clicked()
{
    ui->stackedlab->setCurrentIndex(0);

}


void SmartResearchPublicationManagement::on_BtnPopupCancelInventory_5_clicked()
{
    ui->stackedlab->setCurrentIndex(0);
}

