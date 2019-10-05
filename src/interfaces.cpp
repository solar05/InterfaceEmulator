#include "interfaces.h"
#include "ui_interfaces.h"
#include "../Protocol/serialmessage.h"
#include <QDebug>
#include "iostream"

#define STATE_INIT 1
#define STATE_OPENED 2
#define STATE_CLOSED 3
#define STATE_ERROR 4
#define STATE_NOT_SELECTED 5

using namespace std;

Interfaces::Interfaces(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Interfaces)
{
    ui->setupUi(this);
    setup();
}

void Interfaces::setup()
{
    QFont font("Times", 18);

    ui->interfaceSelect->addItem("RS485");
    ui->interfaceSelect->addItem("CAN");
    ui->interfaceSelect->addItem("Parallel");
    ui->interfaceSelect->setCurrentRow(0);
    ui->baudLabel->setFont(font);
    ui->output->setReadOnly(true);
    ui->portSelect->setFont(font);
    ui->input->setFont(font);
    ui->interfaceSelect->setFont(font);
    ui->output->setFont(font);
    ui->portState->setAlignment(Qt::AlignCenter);
    ui->portState->setFont(font);
    updatePortStatus(STATE_INIT);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExec()));
    updatePorts();
}

Interfaces::~Interfaces()
{
    delete ui;
}

void Interfaces::updatePortStatus(int state)
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
        case 5:
            ui->portState->setText("Port not selected");
            ui->portState->setStyleSheet("QLabel { background-color : #808000; color : white; }");
            ui->input->setReadOnly(true);
            break;
    }
}

void Interfaces::timerExec()
{
    if (port.bytesAvailable()) {
    QByteArray recievedBytes = port.readAll();
    //char *recievedPacket = recievedBytes.data();
    //SerialMessageMC::Header* gotHeader = SerialMessageMC::getHeader(recievedPacket);
    //unsigned char* gotData             = SerialMessageMC::getData  (recievedPacket);
    //int computedCrc                    = SerialMessageMC::Crc16    (gotData, gotHeader->length - 4);
    //int statusCode = data.at(0);
    //printStatus(statusCode);
    }
}

void Interfaces::printStatus(int statusCode)
{
    switch(statusCode) {
        case 1:
            ui->output->insertPlainText("Interfaces response: OK\n");
            break;
        case 2:
            ui->output->insertPlainText("CAN response: OK\n");
            break;
        case 3:
            ui->output->insertPlainText("Parallel response: OK\n");
            break;
        default:
            ui->output->insertPlainText("Error\n");
            break;
    }
}

SerialMessage setInterface(QString interface, SerialMessage msg)
{
    if (interface == "RS485") {
        msg.setType(SerialMessageMC::Interface::RS485);
    } else if (interface == "CAN") {
        msg.setType(SerialMessageMC::Interface::CAN);
    } else if (interface == "Parallel") {
        msg.setType(SerialMessageMC::Interface::PARALLEL);
    }
    return msg;
}

void Interfaces::on_selectButton_clicked()
{
    ui->output->clear();
    QListWidgetItem *portChoice = ui->portSelect->currentItem();
    if(!portChoice) {
        updatePortStatus(STATE_NOT_SELECTED);
        return;
    }
    QString portName = portChoice->text();
    port.setPortName(portName);
    currentInterface = ui->interfaceSelect->currentItem()->text();
    port.open(QIODevice::ReadWrite);
    port.setBaudRate(9600);
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

void Interfaces::on_closeButton_clicked()
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


void Interfaces::on_sendButton_clicked()
{
    port.flush();
    QString textToSend = ui->input->toPlainText();
    QByteArray preparedText = textToSend.toUtf8();
    SerialMessage msg(textToSend);
    msg = setInterface(currentInterface, msg);
    port.write(msg.getPackedMessage());
    cout << msg.toString();
    port.waitForBytesWritten();
    ui->input->clear();
}

void Interfaces::updatePorts()
{
    ui->portSelect->clear();
    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : ports)
        ui->portSelect->addItem(info.portName());
    if (ui->portSelect->count() < 1) {
        ui->portSelect->addItem("There is no port available,\nplease check ports and press refresh ports button.");
        ui->selectButton->setEnabled(false);
    } else {
        ui->sendButton->setEnabled(true);
    }
}

void Interfaces::on_portRefresh_clicked()
{
    updatePorts();
}
