#include "can.h"
#include "ui_can.h"

CAN::CAN(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAN)
{
    ui->setupUi(this);
}

CAN::~CAN()
{
    delete ui;
}

void CAN::on_pushButton_clicked()
{
    this->close();
}
