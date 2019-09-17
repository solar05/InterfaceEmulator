#include "can.h"
#include "ui_can.h"

CAN::CAN(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAN)
{
    ui->setupUi(this);
    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : ports)
        ui->listWidget->addItem(info.portName());
}

CAN::~CAN()
{
    delete ui;
}

void CAN::on_pushButton_3_clicked()
{
    this->close();
}
