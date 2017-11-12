#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Manager.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <limits>
#include <iostream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->requestsSpinBox->setMinimum(1);
    ui->requestsSpinBox->setMaximum(std::numeric_limits<int>::max());

    ui->bufferSpinBox->setMinimum(1);
    ui->bufferSpinBox->setMaximum(std::numeric_limits<int>::max());

    ui->clientsSpinBox->setMinimum(1);
    ui->clientsSpinBox->setMaximum(std::numeric_limits<int>::max());

    ui->serversSpinBox->setMinimum(1);
    ui->serversSpinBox->setMaximum(std::numeric_limits<int>::max());

    const int precision = 4;
    const double step = 0.05;

    ui->aDoubleSpinBox->setMinimum(std::numeric_limits<double>::lowest());
    ui->aDoubleSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->aDoubleSpinBox->setDecimals(precision);
    ui->aDoubleSpinBox->setSingleStep(step);

    ui->bDoubleSpinBox->setMinimum(std::numeric_limits<double>::lowest());
    ui->bDoubleSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->bDoubleSpinBox->setDecimals(precision);
    ui->bDoubleSpinBox->setSingleStep(step);

    ui->lambdaDoubleSpinBox->setMinimum(0.0001);
    ui->lambdaDoubleSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->lambdaDoubleSpinBox->setDecimals(precision);
    ui->lambdaDoubleSpinBox->setSingleStep(step);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{

}

void MainWindow::on_pushButton_clicked()
{
    int requestsCount = ui->requestsSpinBox->text().toInt();
    int bufferSize = ui->bufferSpinBox->text().toInt();
    int clientCount = ui->clientsSpinBox->text().toInt();
    int serverCount = ui->serversSpinBox->text().toInt();

    QLocale russian(QLocale::Russian);
    QString aString = ui->aDoubleSpinBox->text();
    QString bString = ui->bDoubleSpinBox->text();
    QString lambdaString = ui->lambdaDoubleSpinBox->text();

    double a = russian.toDouble(aString);
    double b = russian.toDouble(bString);
    double lambda = russian.toDouble(lambdaString);

    Manager manager = Manager();
    manager.start(requestsCount, bufferSize, clientCount, serverCount, a, b, lambda);
}
