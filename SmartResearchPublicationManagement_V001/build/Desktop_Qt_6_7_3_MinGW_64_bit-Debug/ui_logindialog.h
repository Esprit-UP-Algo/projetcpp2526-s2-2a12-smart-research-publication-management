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
    QLabel *logoLabel;
    QLabel *label_4;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(716, 478);
        LoginDialog->setStyleSheet(QString::fromUtf8("/* ===== Window ===== */\n"
"QDialog#LoginDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                                stop:0 #f4fbfb, stop:1 #e9f7f7);\n"
"    font-family: Consolas;\n"
"}\n"
"\n"
"/* ===== Glass Card ===== */\n"
"QGroupBox#groupBox_2 {\n"
"    background: rgba(255, 255, 255, 190);\n"
"    border: 1px solid rgba(0, 77, 64, 40);\n"
"    border-radius: 18px;\n"
"}\n"
"\n"
"/* Title */\n"
"QLabel#label {\n"
"    color: #004D40;\n"
"    font-size: 22pt;\n"
"    font-weight: 800;\n"
"}\n"
"\n"
"/* Inputs */\n"
"QLineEdit {\n"
"    background: rgba(255,255,255,210);\n"
"    border: 1px solid rgba(0, 206, 209, 90);\n"
"    border-radius: 12px;\n"
"    padding: 10px 12px;\n"
"    color: #123;\n"
"    font-size: 12pt;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid rgba(0, 206, 209, 180);\n"
"}\n"
"\n"
"/* Small labels (Username/Password text) */\n"
"QLabel#label_2, QLabel#label_3 {\n"
"    color: #0e4d4d;\n"
"    font-size: 11pt;\n"
"}\n"
"\n"
"/* Buttons */\n"
"QPush"
                        "Button#btnLogin {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #00CED1, stop:1 #7FFFD4);\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"    padding: 10px 14px;\n"
"    color: #002b2b;\n"
"    font-size: 12pt;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton#btnLogin:hover { opacity: 0.92; }\n"
"\n"
"QPushButton#Quitter {\n"
"    background: rgba(0, 77, 64, 18);\n"
"    border: 1px solid rgba(0, 77, 64, 60);\n"
"    border-radius: 14px;\n"
"    padding: 10px 14px;\n"
"    color: #004D40;\n"
"    font-size: 12pt;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton#Quitter:hover { background: rgba(0, 77, 64, 26); }\n"
"\n"
"/* Logo */\n"
"QLabel#LogoLabel {\n"
"    background: transparent;\n"
"}\n"
""));
        groupBox_2 = new QGroupBox(LoginDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(140, 70, 431, 341));
        lePassword = new QLineEdit(groupBox_2);
        lePassword->setObjectName("lePassword");
        lePassword->setGeometry(QRect(150, 170, 171, 51));
        lePassword->setEchoMode(QLineEdit::EchoMode::Password);
        lePassword->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 180, 81, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        font.setPointSize(11);
        label_3->setFont(font);
        btnLogin = new QPushButton(groupBox_2);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(80, 240, 131, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        btnLogin->setFont(font1);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 100, 81, 20));
        label_2->setFont(font);
        Quitter = new QPushButton(groupBox_2);
        Quitter->setObjectName("Quitter");
        Quitter->setGeometry(QRect(230, 240, 141, 41));
        Quitter->setFont(font1);
        leUsername = new QLineEdit(groupBox_2);
        leUsername->setObjectName("leUsername");
        leUsername->setGeometry(QRect(150, 90, 171, 51));
        leUsername->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 0, 171, 61));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Consolas")});
        font2.setPointSize(20);
        font2.setBold(true);
        label->setFont(font2);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        logoLabel = new QLabel(LoginDialog);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(489, 40, 160, 151));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logoLabel->sizePolicy().hasHeightForWidth());
        logoLabel->setSizePolicy(sizePolicy);
        logoLabel->setMinimumSize(QSize(140, 140));
        logoLabel->setMaximumSize(QSize(160, 160));
        logoLabel->setStyleSheet(QString::fromUtf8("/* ===== Window ===== */\n"
"QDialog#LoginDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                                stop:0 #f4fbfb, stop:1 #e9f7f7);\n"
"    font-family: Consolas;\n"
"}\n"
"\n"
"/* ===== Glass Card ===== */\n"
"QGroupBox#groupBox_2 {\n"
"    background: rgba(255, 255, 255, 190);\n"
"    border: 1px solid rgba(0, 77, 64, 40);\n"
"    border-radius: 18px;\n"
"}\n"
"\n"
"/* Title */\n"
"QLabel#label {\n"
"    color: #004D40;\n"
"    font-size: 22pt;\n"
"    font-weight: 800;\n"
"}\n"
"\n"
"/* Inputs */\n"
"QLineEdit {\n"
"    background: rgba(255,255,255,210);\n"
"    border: 1px solid rgba(0, 206, 209, 90);\n"
"    border-radius: 12px;\n"
"    padding: 10px 12px;\n"
"    color: #123;\n"
"    font-size: 12pt;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid rgba(0, 206, 209, 180);\n"
"}\n"
"\n"
"/* Small labels (Username/Password text) */\n"
"QLabel#label_2, QLabel#label_3 {\n"
"    color: #0e4d4d;\n"
"    font-size: 11pt;\n"
"}\n"
"\n"
"/* Buttons */\n"
"QPush"
                        "Button#btnLogin {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #00CED1, stop:1 #7FFFD4);\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"    padding: 10px 14px;\n"
"    color: #002b2b;\n"
"    font-size: 12pt;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton#btnLogin:hover { opacity: 0.92; }\n"
"\n"
"QPushButton#Quitter {\n"
"    background: rgba(0, 77, 64, 18);\n"
"    border: 1px solid rgba(0, 77, 64, 60);\n"
"    border-radius: 14px;\n"
"    padding: 10px 14px;\n"
"    color: #004D40;\n"
"    font-size: 12pt;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton#Quitter:hover { background: rgba(0, 77, 64, 26); }\n"
"\n"
"/* Logo */\n"
"QLabel#LogoLabel {\n"
"    background: transparent;\n"
"}\n"
""));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/styles/images/vortex.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4 = new QLabel(LoginDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(479, 40, 151, 151));
        label_4->setMinimumSize(QSize(120, 120));
        label_4->setMaximumSize(QSize(160, 160));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/styles/images/logo_off.png")));
        label_4->setScaledContents(true);
        label->raise();
        groupBox_2->raise();
        logoLabel->raise();
        label_4->raise();

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        groupBox_2->setTitle(QString());
        lePassword->setText(QString());
        lePassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Connect", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Username", nullptr));
        Quitter->setText(QCoreApplication::translate("LoginDialog", "Quit", nullptr));
        leUsername->setText(QString());
        leUsername->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Username", nullptr));
        label->setStyleSheet(QCoreApplication::translate("LoginDialog", "font-size: 20pt; font-weight: bold;", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Log in", nullptr));
        logoLabel->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
