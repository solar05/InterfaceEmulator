#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rs485.h"
#include "can.h"
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
        RS485 *rs = new RS485();
        rs->show();
    } else if (choice == "CAN") {
        CAN *can = new CAN;
        can->show();
    }
}
