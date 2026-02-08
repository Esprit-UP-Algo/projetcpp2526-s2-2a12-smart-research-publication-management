#include "smartresearchpublicationmanagement.h"
#include "ui_smartresearchpublicationmanagement.h"

#include <QFile>
#include <QMessageBox>
#include <QDate>

SmartResearchPublicationManagement::SmartResearchPublicationManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartResearchPublicationManagement)
{
    ui->setupUi(this);

    applyTheme(":/styles/light.qss");

    ui->Pages->setCurrentWidget(ui->PageFinance);
    ui->LabsStack->setCurrentIndex(0);
    ui->LabsSpec->addItems({"Toutes","int","ext"});
    ui->LabsCap->addItems({"Toutes","disponible","occupé"});
    ui->LabSpec->addItems({"int","ext"});
    ui->LabCap->addItems({"disponible","occupé"});
}

SmartResearchPublicationManagement::~SmartResearchPublicationManagement()
{
    delete ui;
}

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

void SmartResearchPublicationManagement::on_BtnEmployee_clicked(){ ui->Pages->setCurrentWidget(ui->PageEmployee); }
void SmartResearchPublicationManagement::on_BtnFinance_clicked(){ ui->Pages->setCurrentWidget(ui->PageFinance); }
void SmartResearchPublicationManagement::on_BtnPublication_clicked(){ ui->Pages->setCurrentWidget(ui->PagePublication); }
void SmartResearchPublicationManagement::on_BtnLabs_clicked(){ ui->Pages->setCurrentWidget(ui->PageLabs); }
void SmartResearchPublicationManagement::on_BtnInventory_clicked(){ ui->Pages->setCurrentWidget(ui->PageInventory); }
void SmartResearchPublicationManagement::on_BtnPlans_clicked(){ ui->Pages->setCurrentWidget(ui->PagePlans); }







void SmartResearchPublicationManagement::on_BtnPopupSaveFinance_clicked()
{
    QMessageBox::information(this, "OK", "Transaction enregistrée (démo).");
}




void SmartResearchPublicationManagement::on_BtnPopupCancelInv_clicked()
{
    ui->LabsStack->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnPopupSaveInv_clicked()
{
    ui->LabsStack->setCurrentIndex(0);
    QMessageBox::information(this, "OK", "Produit enregistré (démo).");
}


void SmartResearchPublicationManagement::on_BtnLabAdd_clicked()
{
    ui->LabsStack->setCurrentIndex(1);
    ui->PopupTitleLabs->setText("Ajouter un laboratoire");

    ui->LabName->clear();
    ui->LabResponsible->clear();
    ui->LabLocation->clear();
    ui->LabNumber->clear();
    ui->LabSpec->setCurrentIndex(0);
    ui->LabCap->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnLabEdit_clicked()
{
    ui->LabsStack->setCurrentIndex(1);
    ui->PopupTitleLabs->setText("Modifier le laboratoire");
}

void SmartResearchPublicationManagement::on_BtnPopupCancelLabs_clicked()
{
    ui->LabsStack->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnPopupSaveLabs_clicked()
{
    ui->LabsStack->setCurrentIndex(0);
    QMessageBox::information(this, "OK", "Laboratoire enregistré (démo).");
}

void SmartResearchPublicationManagement::on_BtnPopupResetLabs_clicked()
{
    ui->LabName->clear();
    ui->LabResponsible->clear();
    ui->LabLocation->clear();
    ui->LabNumber->clear();
    ui->LabSpec->setCurrentIndex(0);
    ui->LabCap->setCurrentIndex(0);
}
