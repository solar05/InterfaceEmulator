#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font("Times", 18);
    ui->portSelect->setFont(font);
    ui->input->setFont(font);
    ui->output->setFont(font);
    ui->interfaceChoose->addItem("RS485");
    ui->interfaceChoose->addItem("CAN");
    ui->baudChoose->addItem("9600");
    ui->baudChoose->addItem("19200");
    ui->baudChoose->addItem("38400");
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExec()));
    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : ports)
        ui->portSelect->addItem(info.portName());
    //ui->listWidget->setEnabled(false);
    //QString choice = ui->listWidget->currentItem()->text();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectButton_clicked()
{
    QString portChoice = ui->portSelect->currentItem()->text();
    QString baudRate = ui->baudChoose->currentItem()->text();
    QString selectedInterface = ui->interfaceChoose->currentItem()->text();
    //setInterface(selectedInterface);
    qDebug() << selectedInterface;
    qDebug() << portChoice;
    qDebug() << baudRate.toInt();
    port.setPortName(portChoice);
    port.open(QIODevice::ReadWrite);
    port.setBaudRate(QSerialPort::Baud9600);
    port.setDataBits(dataBits);
    port.setParity(parity);
    port.setStopBits(stopBits);
    port.setFlowControl(flowControl);
    if (port.isOpen()) {
        ui->output->append("Port is opened\n");
        timer->start(500);
        //ui->textEdit_2->setReadOnly(false);
    } else {
        ui->output->append("Port is closed\n");
        timer->stop();
        //ui->textEdit_2->setReadOnly(true);
    }
}

void MainWindow::on_closeButton_clicked()
{
    port.close();
    if (!port.isOpen()) {
        timer->stop();
    }
    ui->output->clear();
    ui->output->append("Port is closed\n");
}

void MainWindow::on_pushButton_clicked()
{
    QString textToSend = ui->input->toPlainText().append('\n');
    port.write(textToSend.toUtf8());
    qDebug() << interface + textToSend;
    qDebug() << textToSend.toUtf8();
    ui->input->clear();
}

void MainWindow::timerExec()
{

    QByteArray data = port.readLine();
    qDebug() << QString::fromUtf8(data);
    if (data == "") {
        return;
    } else {
        //ui->textEdit->insertPlainText(data);
        qDebug() << 2;
    }
}


void MainWindow::setBaud(int baud)
{
    switch (baud) {
        case 9600:
            port.setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            port.setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            port.setBaudRate(QSerialPort::Baud38400);
            break;
    }
}

void MainWindow::setInterface(QString selectedInterface)
{
    if (selectedInterface == "RS485") {
        currentInterface = interface[0];
    } else if (selectedInterface == "CAN") {
        currentInterface = interface[1];
    }
}
