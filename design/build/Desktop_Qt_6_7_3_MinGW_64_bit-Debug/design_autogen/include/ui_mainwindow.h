/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widgetBg;
    QGroupBox *card_2;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit;
    QPushButton *QPushButton_2;
    QPushButton *QPushButton_3;
    QPushButton *QPushButton;
    QPushButton *delete_2;
    QGroupBox *sidebar;
    QPushButton *QPushButton_5;
    QPushButton *QPushButton_6;
    QPushButton *QPushButton_8;
    QPushButton *QPushButton_7;
    QPushButton *QPushButton_9;
    QPushButton *QPushButton_10;
    QPushButton *QPushButton_11;
    QWidget *widget_2;
    QLabel *logoo1;
    QLabel *PUBLICATION;
    QGroupBox *card;
    QWidget *widget;
    QLabel *labelStatistique;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1349, 717);
        MainWindow->setStyleSheet(QString::fromUtf8("/* =========================\n"
"   BASE APP\n"
"========================= */\n"
"QWidget{\n"
"    font-family: \"Segoe UI\", \"Poppins\";\n"
"    font-size: 10.5pt;\n"
"    color: #111827;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMainWindow{\n"
"    background-color: #F7F7FB;\n"
"}\n"
"\n"
"/* =========================\n"
"   \"CARDS\" / PANELS\n"
"========================= */\n"
"QFrame#card, QWidget#card{\n"
"    background-color: rgba(255,255,255,210);\n"
"    border: 1px solid rgba(17,24,39,35);\n"
"    border-radius: 16px;\n"
"}\n"
"\n"
"/* =========================\n"
"   SIDEBAR\n"
"========================= */\n"
"QFrame#sidebar{\n"
"    background-color: rgba(255,255,255,200);\n"
"    border-right: 1px solid rgba(17,24,39,30);\n"
"    border-radius: 18px;\n"
"}\n"
"\n"
"/* Boutons menu */\n"
"QPushButton#navBtn{\n"
"    background: rgba(255,255,255,160);\n"
"    border: 1px solid rgba(17,24,39,28);\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    text-align: left;\n"
"    colo"
                        "r: #111827;\n"
"}\n"
"\n"
"QPushButton#navBtn:hover{\n"
"    background: rgba(0,206,209,35);\n"
"    border: 1px solid rgba(0,206,209,120);\n"
"}\n"
"\n"
"QPushButton#navBtn:checked{\n"
"    background: rgba(0,206,209,55);\n"
"    border: 1px solid rgba(0,206,209,170);\n"
"    color: #0F172A;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* =========================\n"
"   TITLES / LABELS\n"
"========================= */\n"
"QLabel#titleLabel{\n"
"    background-color: rgba(255,255,255,170);\n"
"    border: 1px solid rgba(17,24,39,30);\n"
"    border-radius: 18px;\n"
"    padding: 10px 22px;\n"
"\n"
"    font-size: 18pt;\n"
"    font-weight: 700;\n"
"    letter-spacing: 1px;\n"
"    color: #0F172A;\n"
"}\n"
"\n"
"QLabel#mutedLabel{\n"
"    color: #6B7280;\n"
"}\n"
"\n"
"/* =========================\n"
"   INPUTS\n"
"========================= */\n"
"QLineEdit, QPlainTextEdit, QTextEdit, QSpinBox, QDoubleSpinBox, QDateEdit, QComboBox{\n"
"    background-color: rgba(255,255,255,220);\n"
"    border: 1px solid rgba(17,"
                        "24,39,30);\n"
"    border-radius: 12px;\n"
"    padding: 8px 12px;\n"
"    selection-background-color: rgba(0,206,209,70);\n"
"}\n"
"\n"
"QLineEdit:focus, QPlainTextEdit:focus, QTextEdit:focus, QComboBox:focus{\n"
"    border: 1px solid rgba(0,206,209,180);\n"
"}\n"
"\n"
"/* ComboBox */\n"
"QComboBox::drop-down{\n"
"    border: none;\n"
"    width: 30px;\n"
"}\n"
"QComboBox::down-arrow{\n"
"    width: 10px; height: 10px;\n"
"}\n"
"\n"
"/* =========================\n"
"   BUTTONS (Modern)\n"
"========================= */\n"
"QPushButton{\n"
"    background: rgba(255,255,255,220);\n"
"    border: 1px solid rgba(17,24,39,35);\n"
"    border-radius: 12px;\n"
"    padding: 9px 16px;\n"
"    color: #111827;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background: rgba(0,206,209,35);\n"
"    border: 1px solid rgba(0,206,209,140);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    background: rgba(0,206,209,55);\n"
"}\n"
"\n"
"/* Primary button */\n"
"QPushButton#primaryBtn{\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2"
                        ":1, stop:0 #7FFFD4, stop:1 #00CED1);\n"
"    border: none;\n"
"    color: #0B1220;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton#primaryBtn:hover{\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #61F0D9, stop:1 #00B8BD);\n"
"    color: white;\n"
"}\n"
"QPushButton#primaryBtn:pressed{\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #41D8C4, stop:1 #009095);\n"
"}\n"
"\n"
"/* Danger button (supprimer) */\n"
"QPushButton#dangerBtn{\n"
"    background: #E53935;\n"
"    border: none;\n"
"    color: white;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton#dangerBtn:hover{ background: #D32F2F; }\n"
"QPushButton#dangerBtn:pressed{ background: #B71C1C; }\n"
"\n"
"/* Disabled */\n"
"QPushButton:disabled{\n"
"    background: #E5E7EB;\n"
"    color: #9CA3AF;\n"
"    border: 1px solid #D1D5DB;\n"
"}\n"
"\n"
"/* =========================\n"
"   GROUPBOX (glass)\n"
"========================= */\n"
"QGroupBox{\n"
"    background-color: rgba(255,255,255,85);\n"
"    border: 1px solid rgba(255,25"
                        "5,255,140);\n"
"    border-radius: 18px;\n"
"    margin-top: 18px;\n"
"    padding: 14px;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 4px 12px;\n"
"    margin-left: 14px;\n"
"    background-color: rgba(255,255,255,120);\n"
"    border: 1px solid rgba(255,255,255,150);\n"
"    border-radius: 10px;\n"
"    font-weight: 700;\n"
"    color: #0F172A;\n"
"}\n"
"\n"
"/* =========================\n"
"   TABLE / TREE\n"
"========================= */\n"
"QTableView, QTreeView{\n"
"    background: rgba(255,255,255,210);\n"
"    border: 1px solid rgba(17,24,39,30);\n"
"    border-radius: 14px;\n"
"    gridline-color: rgba(17,24,39,18);\n"
"    selection-background-color: rgba(0,206,209,55);\n"
"    selection-color: #0B1220;\n"
"}\n"
"\n"
"QHeaderView::section{\n"
"    background-color: rgba(255,255,255,230);\n"
"    border: none;\n"
"    border-bottom: 1px solid rgba(17,24,39,25);\n"
"    padding: 8px 10px;\n"
"    font-weight: 700;\n"
"    co"
                        "lor: #0F172A;\n"
"}\n"
"\n"
"QTableView::item{\n"
"    padding: 6px;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"QTableView::item:hover{\n"
"    background: rgba(0,206,209,25);\n"
"}\n"
"\n"
"/* =========================\n"
"   SCROLLBAR (clean)\n"
"========================= */\n"
"QScrollBar:vertical{\n"
"    background: transparent;\n"
"    width: 10px;\n"
"    margin: 8px 4px 8px 4px;\n"
"}\n"
"QScrollBar::handle:vertical{\n"
"    background: rgba(17,24,39,60);\n"
"    border-radius: 5px;\n"
"    min-height: 30px;\n"
"}\n"
"QScrollBar::handle:vertical:hover{\n"
"    background: rgba(0,206,209,180);\n"
"}\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical{\n"
"    height: 0px;\n"
"    background: transparent;\n"
"}\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{\n"
"    background: transparent;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("/* Fond principal (image Vortex) */\n"
"QWidget#centralwidget {\n"
"    background-image: url(:/img/background.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"}\n"
"\n"
"/* TOUS les widgets sont blancs par d\303\251faut */\n"
"QWidget {\n"
"    background-color: white;\n"
"}\n"
"\n"
"/* GroupBox blancs et visibles */\n"
"QGroupBox {\n"
"    background-color: white;\n"
"    border: 1px solid #CCCCCC;\n"
"    border-radius: 8px;\n"
"}\n"
""));
        widgetBg = new QWidget(centralwidget);
        widgetBg->setObjectName("widgetBg");
        widgetBg->setGeometry(QRect(-20, -130, 1411, 821));
        widgetBg->setStyleSheet(QString::fromUtf8("QWidget#widgetBg {\n"
"    background-position: center;\n"
"	background-image: url(:/background/background - Copy.png);\n"
"    background-repeat: no-repeat;\n"
"    background-color: white;\n"
"    border-radius: 12px;\n"
"}\n"
""));
        card_2 = new QGroupBox(widgetBg);
        card_2->setObjectName("card_2");
        card_2->setGeometry(QRect(210, 220, 471, 561));
        tableWidget = new QTableWidget(card_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 13)
            tableWidget->setRowCount(13);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem15);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 60, 461, 381));
        lineEdit = new QLineEdit(card_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(270, 20, 191, 31));
        QPushButton_2 = new QPushButton(card_2);
        QPushButton_2->setObjectName("QPushButton_2");
        QPushButton_2->setGeometry(QRect(20, 460, 121, 31));
        QPushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_3 = new QPushButton(card_2);
        QPushButton_3->setObjectName("QPushButton_3");
        QPushButton_3->setGeometry(QRect(170, 460, 121, 31));
        QPushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton = new QPushButton(card_2);
        QPushButton->setObjectName("QPushButton");
        QPushButton->setGeometry(QRect(320, 460, 121, 31));
        QPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        delete_2 = new QPushButton(card_2);
        delete_2->setObjectName("delete_2");
        delete_2->setGeometry(QRect(170, 510, 121, 31));
        delete_2->setStyleSheet(QString::fromUtf8("QPushButton#delete_2 {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #FF4D4D,\n"
"                                stop:1 #B71C1C);\n"
"    color: white;\n"
"    border: 2px solid #FF6B6B;\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton#delete_2:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #E53935,\n"
"                                stop:1 #8E0000);\n"
"    border: 2px solid #FF8A80;\n"
"}\n"
"\n"
"QPushButton#delete_2:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #C62828,\n"
"                                stop:1 #6A0000);\n"
"    border: 2px solid #FF5252;\n"
"}\n"
""));
        sidebar = new QGroupBox(widgetBg);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(20, 130, 131, 691));
        QPushButton_5 = new QPushButton(sidebar);
        QPushButton_5->setObjectName("QPushButton_5");
        QPushButton_5->setGeometry(QRect(0, 120, 131, 51));
        QPushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_6 = new QPushButton(sidebar);
        QPushButton_6->setObjectName("QPushButton_6");
        QPushButton_6->setGeometry(QRect(0, 200, 131, 51));
        QPushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_8 = new QPushButton(sidebar);
        QPushButton_8->setObjectName("QPushButton_8");
        QPushButton_8->setGeometry(QRect(0, 360, 131, 51));
        QPushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_7 = new QPushButton(sidebar);
        QPushButton_7->setObjectName("QPushButton_7");
        QPushButton_7->setGeometry(QRect(0, 440, 131, 51));
        QPushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_9 = new QPushButton(sidebar);
        QPushButton_9->setObjectName("QPushButton_9");
        QPushButton_9->setGeometry(QRect(0, 510, 131, 51));
        QPushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_10 = new QPushButton(sidebar);
        QPushButton_10->setObjectName("QPushButton_10");
        QPushButton_10->setGeometry(QRect(0, 280, 131, 51));
        QPushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        QPushButton_11 = new QPushButton(sidebar);
        QPushButton_11->setObjectName("QPushButton_11");
        QPushButton_11->setGeometry(QRect(10, 590, 111, 61));
        QPushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #2F80ED,\n"
"                                stop:1 #27AE60);\n"
"    color: white;\n"
"    border: 2px solid #3FF5C0;   /* bordure n\303\251on */\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1F6ED4,\n"
"                                stop:1 #1E8E4E);\n"
"    border: 2px solid #6FFFE9;   /* n\303\251on plus fort */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,\n"
"                                stop:0 #1A5FC2,\n"
"                                stop:1 #187A43);\n"
"    border: 2px solid #1EE6A5;\n"
"}\n"
""));
        widget_2 = new QWidget(sidebar);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 30, 120, 80));
        widget_2->setStyleSheet(QString::fromUtf8("border-image: url(:/logoo/plogo.png);"));
        logoo1 = new QLabel(sidebar);
        logoo1->setObjectName("logoo1");
        logoo1->setGeometry(QRect(20, 260, 91, 71));
        logoo1->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QLabel#logoo1 {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    image: url(:/logo1/logo1.png);\n"
"}\n"
""));
        PUBLICATION = new QLabel(sidebar);
        PUBLICATION->setObjectName("PUBLICATION");
        PUBLICATION->setGeometry(QRect(20, 300, 101, 31));
        PUBLICATION->setStyleSheet(QString::fromUtf8("QLabel#PUBLICATION {\n"
"	color: rgb(255, 255, 255);\n"
"    background-color: transparent;\n"
"    border: none;\n"
"\n"
"}"));
        card = new QGroupBox(widgetBg);
        card->setObjectName("card");
        card->setGeometry(QRect(730, 460, 621, 331));
        widget = new QWidget(card);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 30, 541, 291));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/statistique/statistique.png);"));
        labelStatistique = new QLabel(widgetBg);
        labelStatistique->setObjectName("labelStatistique");
        labelStatistique->setGeometry(QRect(730, 420, 221, 51));
        labelStatistique->setStyleSheet(QString::fromUtf8("QLabel#labelStatistique {\n"
"    color: #E8D8B5;                /* Beige clair */\n"
"    background-color: #1E1E1E;     /* Fond sombre */\n"
"    \n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"    \n"
"    padding: 10px 18px;\n"
"    border-radius: 12px;\n"
"\n"
"    border: 2px solid #E8D8B5;\n"
"\n"
"    /* Effet n\303\251on */\n"
"    text-shadow: \n"
"        0 0 5px  #E8D8B5,\n"
"        0 0 10px #E8D8B5,\n"
"        0 0 20px #CBB98A;\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1349, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        card_2->setTitle(QCoreApplication::translate("MainWindow", "INFO", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "rayen", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        QPushButton_2->setText(QCoreApplication::translate("MainWindow", "ADD", nullptr));
        QPushButton_3->setText(QCoreApplication::translate("MainWindow", "UPDATE", nullptr));
        QPushButton->setText(QCoreApplication::translate("MainWindow", "READ", nullptr));
        delete_2->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        sidebar->setTitle(QString());
        QPushButton_5->setText(QCoreApplication::translate("MainWindow", "EMPLOYEE", nullptr));
        QPushButton_6->setText(QCoreApplication::translate("MainWindow", "FINANCE", nullptr));
        QPushButton_8->setText(QCoreApplication::translate("MainWindow", "LABS", nullptr));
        QPushButton_7->setText(QCoreApplication::translate("MainWindow", "INVENTORY", nullptr));
        QPushButton_9->setText(QCoreApplication::translate("MainWindow", "PLANS", nullptr));
        QPushButton_10->setText(QString());
        QPushButton_11->setText(QCoreApplication::translate("MainWindow", "LOG OUT", nullptr));
        logoo1->setText(QString());
        PUBLICATION->setText(QCoreApplication::translate("MainWindow", " PUBLICATION", nullptr));
        card->setTitle(QString());
        labelStatistique->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
