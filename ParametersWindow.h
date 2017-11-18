#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QWidget>

namespace Ui {
class ParametersWindow;
}

class ParametersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ParametersWindow(QWidget *parent = 0);
    ~ParametersWindow();
signals:
    void changeStackedWidgetIndex(int index);
    void fillTable(int requestsCount, int bufferSize,
                             int clientsCount, double serverCount,
                             double a, double b, double lambda);
    void startStepMode(int requestsCount, int bufferSize,
                       int clientsCount, double serverCount,
                       double a, double b, double lambda);


private slots:
    void on_startButton_clicked();

    void on_stepModeButton_clicked();

private:
    Ui::ParametersWindow *ui;
};

#endif // PARAMETERSWINDOW_H
