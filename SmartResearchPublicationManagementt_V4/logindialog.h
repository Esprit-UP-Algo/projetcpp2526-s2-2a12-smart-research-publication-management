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
    int empId() const { return m_empId; }   // ✅ getter

private slots:
    void on_btnLogin_clicked();

    void on_Quitter_clicked();
    void on_btnFaceID_clicked();



private:
    Ui::LoginDialog *ui;
        int m_empId = -1;
};

#endif // LOGINDIALOG_H
