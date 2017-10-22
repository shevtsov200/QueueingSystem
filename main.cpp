#include "Manager.h"
#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello world" << std::endl;
    Manager manager = Manager();
    manager.start();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
