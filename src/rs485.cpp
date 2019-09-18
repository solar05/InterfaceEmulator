#include "rs485.h"
#include "ui_rs485.h"
#include <QDebug>


RS485::RS485(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RS485)
{
    ui->setupUi(this);
    QFont font("Times", 18);
    ui->input->setReadOnly(true);
    ui->baudSelect->addItem("9600");
    ui->baudSelect->addItem("19200");
    ui->baudSelect->addItem("38400");
    ui->interfaceSelect->addItem("RS485");
    ui->interfaceSelect->addItem("CAN");
    ui->baudSelect->setFont(font);
    ui->output->setReadOnly(true);
    ui->portSelect->setFont(font);
    ui->input->setFont(font);
    ui->output->setFont(font);
    auto ports = QSerialPortInfo::availablePorts();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExec()));
    for (const QSerialPortInfo& info : ports)
        ui->portSelect->addItem(info.portName());
}

RS485::~RS485()
{
    delete ui;
}

void RS485::timerExec()
{
    QByteArray data = port.readLine();
    //qDebug() << QString::fromUtf8(data);
    if (data == "") {
        return;
    } else {
        ui->output->insertPlainText(data);
    }
}



void RS485::on_selectButton_clicked()
{
    ui->output->clear();
    QString portChoice = ui->portSelect->currentItem()->text();
    QString baudRate = ui->baudSelect->currentItem()->text();
    QString selectedInterface = ui->interfaceSelect->currentItem()->text();
    setInterface(selectedInterface);
    port.setPortName(portChoice);
    port.open(QIODevice::ReadWrite);
    port.setBaudRate(baudRate.toInt());
    port.setDataBits(dataBits);
    port.setParity(parity);
    port.setStopBits(stopBits);
    port.setFlowControl(flowControl);
    port.flush();
    if (port.isOpen()) {
        ui->output->append("Port is open\n");
        timer->start(500);
        ui->input->setReadOnly(false);
    } else {
        ui->output->append("Something wrong with conenction\n");
        timer->stop();
        ui->input->setReadOnly(true);
    }
}

void RS485::on_closeButton_clicked()
{
    port.close();
    if (!port.isOpen()) {
        timer->stop();
    }
    ui->output->clear();
    ui->output->append("Port is closed\n");
}

void RS485::setInterface(QString interface)
{
    if (interface == "RS485") {
        currentInterface = interfaceMap[0];
    } else if (interface == "CAN") {
        currentInterface = interfaceMap[1];
    }
}

void RS485::on_sendButton_clicked()
{
    port.flush();
    QString textToSend = ui->input->toPlainText().append('\n');
    port.write((currentInterface + textToSend).toUtf8());
    /*qDebug() << currentInterface + textToSend;
    qDebug() << textToSend;*/
    ui->input->clear();
}
