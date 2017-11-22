#ifndef STEPMODEWINDOW_H
#define STEPMODEWINDOW_H

#include "SystemState.h"

#include <QWidget>
#include <QLabel>
#include <QString>
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

    void on_backButton_clicked();
signals:
    void changeStackedWidgetIndex(int index);

private:
    Ui::StepModeWindow *ui;
    std::vector<SystemState> states_;
    std::size_t currentStep_;

    const QString EMPTY_TEXT = "empty";

    void goToNextStep();
    void initializeLabel(QLabel * label, QString name);
    void printCurrentState();
};

#endif // STEPMODEWINDOW_H
