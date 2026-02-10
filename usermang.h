#ifndef USERMANG_H
#define USERMANG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EmployeeOnlyWindow; }
QT_END_NAMESPACE

class UserMang : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMang(QWidget *parent = nullptr);
    ~UserMang();

private slots:
    void on_BtnEmployee_2_clicked();

    void on_ADD_user_2_clicked();           // AJOUTER
    void on_pushButton_13_clicked();        // MODIFIER (depuis liste)
    void on_pushButton_14_clicked();        // DÉTAILS
    void on_pushButton_15_clicked();        // SUPPRIMER

    void on_pushButton_36_clicked();        // CANCEL modif
    void on_pushButton_37_clicked();        // SAVE modif

    void on_pushButton_34_clicked();        // RETOUR détails

    void on_Cancel_2_clicked();             // CANCEL ajout
    void on_Update_R_2_clicked();           // SAVE ajout

    // Nouveau slot commun pour TOUS les boutons "UPDATE / MODIFIER"
    void goToUpdatePage();

private:
    Ui::EmployeeOnlyWindow *ui;

    bool hasSelection() const;
    void returnToList();
};

#endif // USERMANG_H
