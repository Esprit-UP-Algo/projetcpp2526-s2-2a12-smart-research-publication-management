#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "faceauth.h" // Ajoute ça en haut
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_btnLogin_clicked();

    void on_Quitter_clicked();
    void on_btnFaceID_clicked();
    void on_btnForgotPass_clicked();



private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
