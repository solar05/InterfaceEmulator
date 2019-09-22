#include "interfaces.h"
#include "ui_interfaces.h"
#include <QDebug>

#define STATE_INIT 1
#define STATE_OPENED 2
#define STATE_CLOSED 3
#define STATE_ERROR 4

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
    ui->baudSelect->setCurrentRow(0);
    ui->interfaceSelect->addItem("RS485");
    ui->interfaceSelect->addItem("CAN");
    ui->interfaceSelect->setCurrentRow(0);
    ui->baudSelect->setFont(font);
    ui->output->setReadOnly(true);
    ui->portSelect->setFont(font);
    ui->input->setFont(font);
    ui->output->setFont(font);
    ui->portState->setAlignment(Qt::AlignCenter);
    updatePortStatus(STATE_INIT);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExec()));
    updatePorts();
}

RS485::~RS485()
{
    delete ui;
}

void RS485::updatePortStatus(int state)
{
    switch(state) {
        case 1:
            ui->portState->setText("Initialized");
            ui->portState->setStyleSheet("QLabel { background-color : #001f3f; color : white; }");
            break;
        case 2:
            ui->portState->setText("Port opened");
            ui->portState->setStyleSheet("QLabel { background-color : #2ECC40; color : black; }");
            break;
        case 3:
            ui->portState->setText("Port closed");
            ui->portState->setStyleSheet("QLabel { background-color : #AAAAAA; color : black; }");
            break;
        case 4:
            ui->portState->setText("Port error");
            ui->portState->setStyleSheet("QLabel { background-color : #FF4136; color : black; }");
            break;
    }
}

void RS485::timerExec()
{
    QByteArray data = port.readLine();
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
        updatePortStatus(STATE_OPENED);
        timer->start(500);
        ui->input->setReadOnly(false);
    } else {
        updatePortStatus(STATE_ERROR);
        timer->stop();
        ui->input->setReadOnly(true);
    }
}

void RS485::on_closeButton_clicked()
{
    port.close();
    if (!port.isOpen()) {
        timer->stop();
        updatePortStatus(STATE_CLOSED);
    } else {
        updatePortStatus(STATE_ERROR);
    }
    ui->output->clear();
}

void RS485::setInterface(QString interface)
{
    if (interface == "RS485") {
        currentInterface = interfaceMap[0];
    } else if (interface == "CAN") {
        currentInterface = interfaceMap[1];
    } else {
        currentInterface = "";
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

void RS485::updatePorts()
{
    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : ports)
        ui->portSelect->addItem(info.portName());
}

void RS485::on_portRefresh_clicked()
{
    ui->portSelect->clear();
    updatePorts();
}
