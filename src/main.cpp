#include "mainwindow.h"

#include <QApplication>
#include <interfaces.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    Interfaces f;
    f.show();
    return a.exec();
}
