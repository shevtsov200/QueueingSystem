#ifndef STEPMODEWINDOW_H
#define STEPMODEWINDOW_H

#include "SystemState.h"

#include <QWidget>
#include <vector>

namespace Ui {
class StepModeWindow;
}

class StepModeWindow : public QWidget
{
    Q_OBJECT

public slots:
    void startStepMode(int requestsCount, int bufferSize,
                   int clientCount, double serverCount,
                   double a, double b, double lambda);
public:
    explicit StepModeWindow(QWidget *parent = 0);
    ~StepModeWindow();

private slots:
    void on_nextStepButton_clicked();

private:
    Ui::StepModeWindow *ui;
    std::vector<SystemState> states_;
    int currentStep_;

    void goToNextStep();
};

#endif // STEPMODEWINDOW_H
