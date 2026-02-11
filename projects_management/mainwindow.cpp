#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    applyLightMode(); // ou applyDarkMode()
    darkMode = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAjouter_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btnRetour_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btnRetour_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btnmodifier_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_btnMode_clicked()
{
    darkMode = !darkMode;

    if (darkMode)
        applyDarkMode();
    else
        applyLightMode();
}
void MainWindow::on_btnMode_2_clicked()
{
    darkMode = !darkMode;

    if (darkMode)
        applyDarkMode();
    else
        applyLightMode();
}
void MainWindow::on_btnMode_3_clicked()
{
    darkMode = !darkMode;

    if (darkMode)
        applyDarkMode();
    else
        applyLightMode();
}

void MainWindow::applyDarkMode()
{
    qApp->setStyleSheet(R"(
        QWidget {
            background-color: #0f1c1f;
            color: #e6fdfc;
            font-family: Segoe UI;
        }

        QGroupBox {
            background-color: #132629;
            border-radius: 12px;
            padding: 8px;
        }

        QPushButton {
            background-color: #1fcac1;
            color: black;
            border-radius: 10px;
            padding: 6px 14px;
        }

        QPushButton:hover {
            background-color: #22e0d6;
        }

        QPushButton:disabled {
            background-color: #555;
            color: #aaa;
        }

        QLineEdit, QComboBox, QDateEdit {
            background-color: #0b1517;
            border: 1px solid #1fcac1;
            border-radius: 8px;
            padding: 6px;
        }

        QTableView {
            background-color: #2b2b2b;
            gridline-color: #444;
            selection-background-color: #007acc;
        }

        QHeaderView::section {
            background-color: #1a2f33;
            padding: 6px;
            border: none;
        }
    )");
}

void MainWindow::applyLightMode()
{
    qApp->setStyleSheet(R"(
        QWidget {
            background-color: #f5fefe;
            color: #003333;
            font-family: Segoe UI;
        }

        QGroupBox {
            background-color: #ffffff;
            border-radius: 12px;
            padding: 8px;
        }

        QPushButton {
            background-color: #00c9c2;
            color: white;
            border-radius: 10px;
            padding: 6px 14px;
        }

        QPushButton:hover {
            background-color: #00b0aa;
        }

        QLineEdit, QComboBox, QDateEdit {
            background-color: white;
            border: 1px solid #00c9c2;
            border-radius: 8px;
            padding: 6px;
        }

        QTableView {
            background-color: #ffffff;
            gridline-color: #ddd;
            selection-background-color: #00c9c2;
        }

        QHeaderView::section {
            background-color: #e9fefe;
            padding: 6px;
            border: none;
        }
    )");
}
