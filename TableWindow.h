#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>
#include "ui_TableWindow.h"


namespace Ui {
class TableWindow;
}

class TableWindow : public QWidget
{
    Q_OBJECT

public slots:
    void fillTable(int requestsCount, int bufferSize,
                   int clientCount, double serverCount,
                   double a, double b, double lambda);

public:
    explicit TableWindow(QWidget *parent = 0);

    template< typename T >
    void setItem(int i, int j, T value);
    void setRowCount(int count);
    void setServerRowCount(int count);
    void setServerTableItems(const std::vector<double> &utilizationFactors);

    ~TableWindow();

private slots:
    void on_backButton_clicked();

private:
    Ui::TableWindow *ui;
};

template< typename T >
void TableWindow::setItem(int i, int j, T value)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole,value);
    ui->clientsTable->setItem(i,j,item);
}

#endif // TABLEWINDOW_H
