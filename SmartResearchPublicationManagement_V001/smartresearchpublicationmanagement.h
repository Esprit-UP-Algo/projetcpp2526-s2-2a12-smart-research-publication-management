#ifndef SMARTRESEARCHPUBLICATIONMANAGEMENT_H
#define SMARTRESEARCHPUBLICATIONMANAGEMENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SmartResearchPublicationManagement; }
QT_END_NAMESPACE

class SmartResearchPublicationManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartResearchPublicationManagement(QWidget *parent = nullptr);
    ~SmartResearchPublicationManagement();

private slots:
    void on_BtnTheme_clicked();

    void on_BtnEmployee_clicked();
    void on_BtnFinance_clicked();
    void on_BtnPublication_clicked();
    void on_BtnLabs_clicked();
    void on_BtnInventory_clicked();
    void on_BtnPlans_clicked();

    void on_BtnAdd_clicked();
    void on_BtnEdit_clicked();
    void on_BtnPopupCancelFinance_clicked();
    void on_BtnPopupSaveFinance_clicked();

    void on_BtnProdAdd_clicked();
    void on_BtnProdEdit_clicked();
    void on_BtnPopupCancelInv_clicked();
    void on_BtnPopupSaveInv_clicked();


    void on_BtnLabAdd_clicked();
    void on_BtnLabEdit_clicked();
    void on_BtnPopupCancelLabs_clicked();
    void on_BtnPopupSaveLabs_clicked();
    void on_BtnPopupResetLabs_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void on_ADD_user_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_33_clicked();

    void on_Update_R_clicked();

    void on_pushButton_11_clicked();

    void on_Cancel_clicked();

    void on_Delete_clicked();

    void on_PDF_clicked();

    void on_pushButton_10_clicked();

private:
    void applyTheme(const QString& qssPath);

    Ui::SmartResearchPublicationManagement *ui;
    bool m_dark = false;
};

#endif
