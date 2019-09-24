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
    setup();
}

void RS485::setup()
{
    QFont font("Times", 18);
    getBauds();
    ui->baudSelect->setCurrentRow(1);
    ui->interfaceSelect->addItem("RS485");
    ui->interfaceSelect->addItem("CAN");
    ui->interfaceSelect->addItem("Parallel");
    ui->interfaceSelect->setCurrentRow(0);
    ui->baudSelect->setFont(font);
    ui->output->setReadOnly(true);
    ui->portSelect->setFont(font);
    ui->input->setFont(font);
    ui->interfaceSelect->setFont(font);
    ui->output->setFont(font);
    ui->portState->setAlignment(Qt::AlignCenter);
    updatePortStatus(STATE_INIT);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExec()));
    updatePorts();
}

void RS485::getBauds()
{
    for (int baud = 4800; baud <= 78600; baud *= 2) {
        ui->baudSelect->addItem(QString::number(baud));
    }
    ui->baudSelect->addItem("115200");
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
            ui->input->setReadOnly(true);
            break;
        case 2:
            ui->portState->setText("Port opened");
            ui->portState->setStyleSheet("QLabel { background-color : #2ECC40; color : black; }");
            ui->input->setReadOnly(false);
            break;
        case 3:
            ui->portState->setText("Port closed");
            ui->portState->setStyleSheet("QLabel { background-color : #AAAAAA; color : black; }");
            ui->input->setReadOnly(true);
            break;
        case 4:
            ui->portState->setText("Port error");
            ui->portState->setStyleSheet("QLabel { background-color : #FF4136; color : black; }");
            ui->input->setReadOnly(true);
            break;
    }
}

void RS485::timerExec()
{
    if (port.bytesAvailable()) {
    QByteArray data = port.readLine();
    int statusCode = data.at(0);
    printStatus(statusCode);
    }
}

void RS485::printStatus(int statusCode)
{
    switch(statusCode) {
        case 1:
            ui->output->insertPlainText("OK");
            break;
        default:
            ui->output->insertPlainText("Error");
            break;
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
    } else {
        updatePortStatus(STATE_ERROR);
        timer->stop();
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
        currentInterface = interfaceMap[0].toUtf8();
    } else if (interface == "CAN") {
        currentInterface = interfaceMap[1].toUtf8();
    } else if (interface == "Parallel") {
        currentInterface = interfaceMap[2].toUtf8();
    } else {
        currentInterface = "\x00";
    }
}

void RS485::on_sendButton_clicked()
{
    port.flush();
    QString textToSend = ui->input->toPlainText().append('\n');
    QByteArray preparedFrame = currentInterface;
    QByteArray preparedText = textToSend.toUtf8();
    int length = preparedText.length() + 2;
    char* buffer = preparedText.data();
    preparedFrame.append(length);
    preparedFrame.append(buffer);
    qDebug() << preparedFrame;
    port.write(preparedFrame);
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
