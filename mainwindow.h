#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort port;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    QTimer *timer;
    QString interface[2] = {"0:", "1:"};
    QString currentInterface;

private slots:
    void setInterface(QString);

    void timerExec();

    void on_selectButton_clicked();

    void on_closeButton_clicked();

    void on_pushButton_clicked();

    void setBaud(int);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
