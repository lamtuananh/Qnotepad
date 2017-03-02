#include "mainwindow.h"
#include "checkthread.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //QMYTHREAD_H mythread;

    MainWindow w;
    w.show();

    return a.exec();
}
