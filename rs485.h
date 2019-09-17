#ifndef RS485_H
#define RS485_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

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
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    QTimer *timer;
    QString interface = "0:";

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void timerExec();

private:
    Ui::RS485 *ui;
};

#endif // RS485_H
