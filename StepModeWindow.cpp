#include "StepModeWindow.h"
#include "ui_StepModeWindow.h"

#include "SystemState.h"
#include "Manager.h"

#include <vector>

void StepModeWindow::startStepMode(int requestsCount, int bufferSize, int clientCount, double serverCount, double a, double b, double lambda)
{
    Manager manager = Manager();
    manager.start(requestsCount, bufferSize, clientCount, serverCount, a, b, lambda);

    states_ = manager.getStates();
    currentStep_ = 0;
}

StepModeWindow::StepModeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepModeWindow)
{
    ui->setupUi(this);
}

StepModeWindow::~StepModeWindow()
{
    delete ui;
}

void StepModeWindow::goToNextStep()
{
    SystemState state = states_[currentStep_];
    Request request = state.clients_[currentStep_].retrieveRequest();
    ui->clientLabel->setText(QString::fromStdString(request.getRequestName()));
}

void StepModeWindow::on_nextStepButton_clicked()
{
    goToNextStep();
}
