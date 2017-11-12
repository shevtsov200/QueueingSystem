#include "TableWindow.h"
#include "ui_TableWindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(1);
    QStringList headerLabels;
    headerLabels << "client" << "requests count"
                            << "p_reject" << "T_sys" << "T_buf"
                            << "T_serv" << "V_buf" << "V_serv";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
}

void TableWindow::setRowCount(int count)
{
    ui->tableWidget->setRowCount(count);
}

TableWindow::~TableWindow()
{
    delete ui;
}
