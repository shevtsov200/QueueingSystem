#include "TableWindow.h"
#include "ui_TableWindow.h"

#include "Manager.h"
#include "Statistics.h"

void TableWindow::fillTable(int requestsCount, int bufferSize, int clientCount, double serverCount, double a, double b, double lambda)
{
    Manager manager = Manager();
    Statistics statistics = manager.start(requestsCount, bufferSize, clientCount, serverCount, a, b, lambda);

    std::vector<int> clientRequestsCounts = statistics.getClientRequestCounts();
    std::vector<double> rejectProbabilities = statistics.getRejectProbabilities();
    std::vector<double> systemStayMeans = statistics.getSystemStayMeans();
    std::vector<double> bufferStayMeans = statistics.getBufferStayMeans();
    std::vector<double> serviceStayMeans = statistics.getServiceStayMeans();
    std::vector<double> bufferVariances = statistics.getBufferVariances();
    std::vector<double> serviceVariances = statistics.getServiceVariances();
    std::vector<double> utilizationFactors = statistics.getUtilizationFactors();

    setRowCount(clientCount);
    setServerRowCount(serverCount);
    setServerTableItems(utilizationFactors);

    for(std::size_t i = 0; i < clientCount; ++i)
    {
        setItem(i,0,i);
        setItem(i,1,clientRequestsCounts[i]);
        setItem(i,2,rejectProbabilities[i]);
        setItem(i,3,systemStayMeans[i]);
        setItem(i,4,bufferStayMeans[i]);
        setItem(i,5,serviceStayMeans[i]);
        setItem(i,6,bufferVariances[i]);
        setItem(i,7,serviceVariances[i]);
    }
}

TableWindow::TableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);

    ui->clientsTable->setColumnCount(8);

    QStringList clientsHeaderLabels;
    clientsHeaderLabels << "client" << "requests count"
                            << "p_reject" << "T_sys" << "T_buf"
                            << "T_serv" << "V_buf" << "V_serv";
    ui->clientsTable->setHorizontalHeaderLabels(clientsHeaderLabels);

    ui->serversTable->setColumnCount(2);
    QStringList serversHeaderLabels;
    serversHeaderLabels << "server" << "utilization factor";
    ui->serversTable->setHorizontalHeaderLabels(serversHeaderLabels);
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

void TableWindow::on_backButton_clicked()
{

}
