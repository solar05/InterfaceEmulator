#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port.flush();
    QFont font("Times", 18);
    //ui->textEdit_2->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->listWidget->setFont(font);
    ui->textEdit->setFont(font);
    ui->textEdit_2->setFont(font);
    auto ports = QSerialPortInfo::availablePorts();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExec()));
    for (const QSerialPortInfo& info : ports)
        ui->listWidget->addItem(info.portName());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    port.flush();
    QString textToSend = ui->textEdit_2->toPlainText().append('\n');
    port.write((interface + textToSend).toUtf8());
    qDebug() << interface + textToSend;
    qDebug() << textToSend;
    ui->textEdit_2->clear();
    port.flush();
}

void MainWindow::on_pushButton_2_clicked()
{
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
        timer->start(500);
        //ui->textEdit_2->setReadOnly(false);
    } else {
        qDebug() << "port is closed";
        timer->stop();
        //ui->textEdit_2->setReadOnly(true);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    port.close();
    if (!port.isOpen()) {
        timer->stop();
    }
    ui->textEdit->clear();
}


void MainWindow::timerExec()
{

    QByteArray data = port.readLine();
    qDebug() << QString::fromUtf8(data);
    if (data == "") {
        return;
    } else {
        ui->textEdit->insertPlainText(data);
    }
}
