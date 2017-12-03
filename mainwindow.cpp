#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Manager.h"
#include "TableWindow.h"
#include "ParametersWindow.h"
#include "StepModeWindow.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <limits>
#include <iostream>
#include <QTextStream>

void MainWindow::openNewWindows()
{

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Queueing System");

    QWidget * tableWindow = new TableWindow();
    QWidget * parametersWindow = new ParametersWindow();
    QWidget * stepModeWindow = new StepModeWindow();

    ui->stackedWidget->addWidget(tableWindow);
    ui->stackedWidget->addWidget(parametersWindow);
    ui->stackedWidget->addWidget(stepModeWindow);
    ui->stackedWidget->setCurrentWidget(parametersWindow);

    connect(parametersWindow,
            SIGNAL(changeStackedWidgetIndex(int)), this,
            SLOT(setCurrentIndex(int)));
    connect(tableWindow, SIGNAL(changeStackedWidgetIndex(int)), this,
            SLOT(setCurrentIndex(int)));
    connect(stepModeWindow, SIGNAL(changeStackedWidgetIndex(int)), this,
            SLOT(setCurrentIndex(int)));
    connect(parametersWindow, SIGNAL(fillTable(int, int,int, double, double, double, double)), tableWindow,
            SLOT(fillTable(int, int,int, double, double, double, double)));
    connect(parametersWindow, SIGNAL(startStepMode(int, int,int, double, double, double, double)), stepModeWindow,
            SLOT(startStepMode(int, int,int, double, double, double, double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
