#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getIdEmploye() const { return m_idEmploye; }
    QString getRole() const { return m_role; }
    ~LoginDialog();

private slots:
    void on_btnLogin_clicked();

    void on_Quitter_clicked();


private:
    Ui::LoginDialog *ui;
    QString m_idEmploye;
    QString m_role;
};

#endif // LOGINDIALOG_H
