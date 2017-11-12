#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Manager.h"

#include <QTableWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(1);
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
    int N = ui->spinBox->text().toInt();
    Manager manager = Manager();
    manager.start(N);
}
