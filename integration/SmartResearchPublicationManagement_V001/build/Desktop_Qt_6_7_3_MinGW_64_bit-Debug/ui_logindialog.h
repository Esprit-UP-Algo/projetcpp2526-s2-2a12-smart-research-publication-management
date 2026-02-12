/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGroupBox *groupBox_2;
    QLineEdit *lePassword;
    QLabel *label_3;
    QPushButton *btnLogin;
    QLabel *label_2;
    QPushButton *Quitter;
    QLineEdit *leUsername;
    QLabel *label;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(716, 478);
        groupBox_2 = new QGroupBox(LoginDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(150, 140, 501, 321));
        lePassword = new QLineEdit(groupBox_2);
        lePassword->setObjectName("lePassword");
        lePassword->setGeometry(QRect(150, 140, 171, 81));
        lePassword->setEchoMode(QLineEdit::EchoMode::Password);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 180, 131, 20));
        btnLogin = new QPushButton(groupBox_2);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(110, 240, 101, 41));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 100, 121, 20));
        Quitter = new QPushButton(groupBox_2);
        Quitter->setObjectName("Quitter");
        Quitter->setGeometry(QRect(230, 240, 111, 41));
        leUsername = new QLineEdit(groupBox_2);
        leUsername->setObjectName("leUsername");
        leUsername->setGeometry(QRect(150, 60, 171, 81));
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 20, 485, 131));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("LoginDialog", "GroupBox", nullptr));
        lePassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Mot de passe", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Se connecter", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "username", nullptr));
        Quitter->setText(QCoreApplication::translate("LoginDialog", "Quitter", nullptr));
        leUsername->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Nom d'utilisateur", nullptr));
        label->setStyleSheet(QCoreApplication::translate("LoginDialog", "font-size: 20pt; font-weight: bold;", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "CONNEXION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
