#include "rs485.h"
#include "ui_rs485.h"
#include <QSerialPort>
#include <QSerialPortInfo>

RS485::RS485(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RS485)
{
    ui->setupUi(this);
    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : ports)
        ui->listWidget->addItem(info.portName());
}

RS485::~RS485()
{
    delete ui;
}

void RS485::on_pushButton_clicked()
{
    this->close();
}
