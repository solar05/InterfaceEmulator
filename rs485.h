#ifndef RS485_H
#define RS485_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class RS485;
}

class RS485 : public QWidget
{
    Q_OBJECT

public:
    explicit RS485(QWidget *parent = nullptr);
    ~RS485();
    QSerialPort port;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::RS485 *ui;
};

#endif // RS485_H
