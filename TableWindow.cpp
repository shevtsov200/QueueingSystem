#include "TableWindow.h"
#include "ui_TableWindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);

    ui->clientsTable->setColumnCount(8);
    //ui->clientsTable->setRowCount(1);
    QStringList clientsHeaderLabels;
    clientsHeaderLabels << "client" << "requests count"
                            << "p_reject" << "T_sys" << "T_buf"
                            << "T_serv" << "V_buf" << "V_serv";
    ui->clientsTable->setHorizontalHeaderLabels(clientsHeaderLabels);

    ui->serversTable->setColumnCount(2);
    QStringList serversHeaderLabels;
    serversHeaderLabels << "server" << "utilization factor";
    ui->serversTable->setHorizontalHeaderLabels(serversHeaderLabels);

    //ui->serversTable->
}

void TableWindow::setRowCount(int count)
{
    ui->clientsTable->setRowCount(count);
}

void TableWindow::setServerRowCount(int count)
{
    ui->serversTable->setRowCount(count);
}

void TableWindow::setServerTableItems(const std::vector<double> &utilizationFactors)
{
    for(std::size_t i = 0; i < utilizationFactors.size(); ++i)
    {
        QTableWidgetItem *serverItem = new QTableWidgetItem();
        serverItem->setData(Qt::DisplayRole,i);
        ui->serversTable->setItem(i,0,serverItem);

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole,utilizationFactors[i]);
        ui->serversTable->setItem(i,1,item);
    }
}

TableWindow::~TableWindow()
{
    delete ui;
}
