#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Manager.h"
#include "TableWindow.h"

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

    //connect(ui->startButton, SIGNAL(clicked()), this, SLOT(openNewWindows()));

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

void MainWindow::on_startButton_clicked()
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
    Statistics statistics = manager.start(requestsCount, bufferSize, clientCount, serverCount, a, b, lambda);

    std::vector<int> clientRequestsCounts = statistics.getClientRequestCounts();
    std::vector<double> rejectProbabilities = statistics.getRejectProbabilities();
    std::vector<double> systemStayMeans = statistics.getSystemStayMeans();
    std::vector<double> bufferStayMeans = statistics.getBufferStayMeans();
    std::vector<double> serviceStayMeans = statistics.getServiceStayMeans();
    std::vector<double> bufferVariances = statistics.getBufferVariances();
    std::vector<double> serviceVariances = statistics.getServiceVariances();

    TableWindow *tableWindow = new TableWindow();
    tableWindow->setRowCount(clientCount);

    for(std::size_t i = 0; i < clientCount; ++i)
    {
        tableWindow->setItem(i,0,i);
        tableWindow->setItem(i,1,clientRequestsCounts[i]);
        tableWindow->setItem(i,2,rejectProbabilities[i]);
        tableWindow->setItem(i,3,systemStayMeans[i]);
        tableWindow->setItem(i,4,bufferStayMeans[i]);
        tableWindow->setItem(i,5,serviceStayMeans[i]);
        tableWindow->setItem(i,6,bufferVariances[i]);
        tableWindow->setItem(i,7,serviceVariances[i]);
    }

    setCentralWidget(tableWindow);
    //tableWidget->setSize
    //tableWidget->resizeColumnsToContents();
    //tableWidget->resize(tableWidget->sizeHint());
    //resize(tableWidget->size());
}
