#include "rs485.h"
#include "ui_rs485.h"
#include <QDebug>


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
    port.close();
    if (port.isOpen()) {
        qDebug() << "port is open";
    } else {
        qDebug() << "port is closed";
    }
    this->close();
}

void RS485::on_pushButton_2_clicked()
{
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    QString portChoice = ui->listWidget->currentItem()->text();
    qDebug() << portChoice;
    port.setPortName(portChoice);
    port.open(QIODevice::ReadWrite);
    port.setBaudRate(QSerialPort::Baud9600);
    port.setDataBits(dataBits);
    port.setParity(parity);
    port.setStopBits(stopBits);
    port.setFlowControl(flowControl);
    if (port.isOpen()) {
        qDebug() << "port is open";
    } else {
        qDebug() << "port is closed";
    }
}

void RS485::on_pushButton_3_clicked()
{
    port.close();
    if (port.isOpen()) {
        qDebug() << "port is open";
    } else {
        qDebug() << "port is closed";
    }
}
