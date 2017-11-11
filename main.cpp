#include "Manager.h"
#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    Manager manager = Manager();
    manager.start();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
