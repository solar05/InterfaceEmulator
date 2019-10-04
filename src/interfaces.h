#ifndef Interfaces_H
#define Interfaces_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

namespace Ui {
class Interfaces;
}

class Interfaces : public QWidget
{
    Q_OBJECT

public:
    explicit Interfaces(QWidget *parent = nullptr);
    ~Interfaces();
    QSerialPort port;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    QTimer *timer;
    QString currentInterface;
    void updatePorts();

private slots:
    void timerExec();

    void on_selectButton_clicked();

    void on_closeButton_clicked();

    void on_sendButton_clicked();

    void on_portRefresh_clicked();

    void updatePortStatus(int);

    void setup();

    void printStatus(int);

private:
    Ui::Interfaces *ui;
};

#endif // Interfaces_H
