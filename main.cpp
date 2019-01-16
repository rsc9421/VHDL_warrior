#include "mainwindow.h"
#include <QApplication>
#include<QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // a.setStyle(QStyleFactory::create("windows"));
    //a.setStyle(QMacStyle());
    a.setStyleSheet("fusion");
    MainWindow w;
    w.show();

    return a.exec();
}
