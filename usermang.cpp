#include "usermang.h"
#include "ui_usermang.h"
#include <QMessageBox>
#include <QDebug>

UserMang::UserMang(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployeeOnlyWindow)
{
    ui->setupUi(this);

    ui->EmployeeStack->setCurrentIndex(0);   // liste par défaut

    // Debug (optionnel)
    qDebug() << "EmployeeStack count:" << ui->EmployeeStack->count();
    for (int i = 0; i < ui->EmployeeStack->count(); ++i) {
        qDebug() << "Index" << i << "→" << ui->EmployeeStack->widget(i)->objectName();
    }
}

UserMang::~UserMang()
{
    delete ui;
}

void UserMang::on_BtnEmployee_2_clicked()
{
    ui->EmployeeStack->setCurrentIndex(0);
}

void UserMang::on_ADD_user_2_clicked()
{
    ui->EmployeeStack->setCurrentIndex(2);   // page ajout
}

void UserMang::on_pushButton_13_clicked()
{
    if (ui->tableWidget_2->currentRow() < 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé.");
        return;
    }
    goToUpdatePage();   // ← on utilise le slot commun
}

void UserMang::on_pushButton_14_clicked()
{
    if (ui->tableWidget_2->currentRow() < 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé.");
        return;
    }
    ui->EmployeeStack->setCurrentIndex(3);   // détails
}

void UserMang::on_pushButton_15_clicked()
{
    if (ui->tableWidget_2->currentRow() < 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé.");
        return;
    }

    if (QMessageBox::question(this, "Confirmation", "Supprimer cet employé ?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        int row = ui->tableWidget_2->currentRow();
        ui->tableWidget_2->removeRow(row);
        QMessageBox::information(this, "Succès", "Employé supprimé (simulation).");
    }
}

void UserMang::on_pushButton_36_clicked()
{
    returnToList();
}

void UserMang::on_pushButton_37_clicked()
{
    QMessageBox::information(this, "Simulation", "Modifications enregistrées.");
    returnToList();
}

void UserMang::on_pushButton_34_clicked()
{
    returnToList();
}

void UserMang::on_Cancel_2_clicked()
{
    returnToList();
}

void UserMang::on_Update_R_2_clicked()
{
    QMessageBox::information(this, "Simulation", "Employé ajouté.");
    returnToList();
}

// Slot commun pour TOUS les boutons "UPDATE / MODIFIER"
void UserMang::goToUpdatePage()
{
    ui->EmployeeStack->setCurrentIndex(1);   // page_update
}

bool UserMang::hasSelection() const
{
    return ui->tableWidget_2->currentRow() >= 0;
}

void UserMang::returnToList()
{
    ui->EmployeeStack->setCurrentIndex(0);
}
