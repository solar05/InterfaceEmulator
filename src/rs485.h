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
    QString interfaceMap[2] = {"0:", "1:"};
    QString currentInterface;

private slots:
    void timerExec();

    void on_selectButton_clicked();

    void on_closeButton_clicked();

    void on_sendButton_clicked();

    void setInterface(QString);

private:
    Ui::RS485 *ui;
};

#endif // RS485_H
