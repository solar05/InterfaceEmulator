#include "rs485.h"
#include "ui_rs485.h"

RS485::RS485(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RS485)
{
    ui->setupUi(this);
}

RS485::~RS485()
{
    delete ui;
}

void RS485::on_pushButton_clicked()
{
    this->close();
}
