#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("RS485");
    ui->listWidget->addItem("CAN");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString choice = ui->listWidget->currentItem()->text();
    if (choice == "RS485") {
        rsWindow->show();
    } else if (choice == "CAN") {
        canWindow->show();
    }
}
