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
    ui->FinanceStack->setCurrentIndex(0);

    ui->CbType->addItems({"Tous","Dépense","Revenu"});
    ui->CbCategory->addItems({"Toutes","Matériel","Service","Transport","Autre"});

    ui->FormType->addItems({"Dépense","Revenu"});
    ui->FormCategory->addItems({"Matériel","Service","Transport","Autre"});
    ui->FormPayMode->addItems({"Cash","Carte","Virement","Chèque"});

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

void SmartResearchPublicationManagement::on_BtnAdd_clicked()
{
    ui->FinanceStack->setCurrentIndex(1);
    ui->PopupTitleFinance->setText("Ajouter une transaction");

    ui->FormCode->clear();
    ui->FormAmount->clear();
    ui->FormDesc->clear();
    ui->FormDate->setDate(QDate::currentDate());
    ui->FormCreatedAt->setDate(QDate::currentDate());
}

void SmartResearchPublicationManagement::on_BtnEdit_clicked()
{
    ui->FinanceStack->setCurrentIndex(1);
    ui->PopupTitleFinance->setText("Modifier la transaction");
}

void SmartResearchPublicationManagement::on_BtnPopupCancelFinance_clicked()
{
    ui->FinanceStack->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnPopupSaveFinance_clicked()
{
    ui->FinanceStack->setCurrentIndex(0);
    QMessageBox::information(this, "OK", "Transaction enregistrée (démo).");
}



