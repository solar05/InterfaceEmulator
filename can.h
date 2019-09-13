#ifndef CAN_H
#define CAN_H

#include <QWidget>

namespace Ui {
class CAN;
}

class CAN : public QWidget
{
    Q_OBJECT

public:
    explicit CAN(QWidget *parent = nullptr);
    ~CAN();

private slots:

    void on_pushButton_3_clicked();

private:
    Ui::CAN *ui;
};

#endif // CAN_H
