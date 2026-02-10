/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *leUsername;
    QLineEdit *lePassword;
    QPushButton *btnLogin;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(503, 235);
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        leUsername = new QLineEdit(centralwidget);
        leUsername->setObjectName("leUsername");

        verticalLayout->addWidget(leUsername);

        lePassword = new QLineEdit(centralwidget);
        lePassword->setObjectName("lePassword");
        lePassword->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(lePassword);

        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName("btnLogin");

        verticalLayout->addWidget(btnLogin);

        Login->setCentralWidget(centralwidget);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QMainWindow *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        label->setStyleSheet(QCoreApplication::translate("Login", "font-size: 20pt; font-weight: bold;", nullptr));
        label->setText(QCoreApplication::translate("Login", "CONNEXION", nullptr));
        leUsername->setPlaceholderText(QCoreApplication::translate("Login", "Nom d'utilisateur", nullptr));
        lePassword->setPlaceholderText(QCoreApplication::translate("Login", "Mot de passe", nullptr));
        btnLogin->setText(QCoreApplication::translate("Login", "Se connecter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
