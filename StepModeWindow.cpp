#include "StepModeWindow.h"
#include "ui_StepModeWindow.h"

#include "SystemState.h"
#include "Manager.h"

#include <vector>
#include <iostream>

void StepModeWindow::startStepMode(int requestsCount, int bufferSize, int clientCount, double serverCount, double a, double b, double lambda)
{
    Manager manager = Manager();
    manager.start(requestsCount, bufferSize, clientCount, serverCount, a, b, lambda);

    states_ = manager.getStates();
    currentStep_ = 0;

    for(std::size_t i = 0; i < states_.back().servers_.size(); ++i)
    {
        QLabel *label = new QLabel();
        label->setText("empty");
        label->setMinimumWidth(100);
        label->setObjectName(QString::fromStdString(states_.back().servers_[i].getServerName()));
        ui->verticalLayout->addWidget(label);
    }

    ui->clientLabel->setText("empty");
    ui->bufferLabel->setText("empty");

    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    int i = 0;
    for(auto it = states_.cbegin(); it != states_.cend(); ++it)
    {
        std::cout << i++ << std::endl;
        it->buffer_.print();
        std::for_each(it->servers_.begin(),it->servers_.end(),
                      [](const Server & server)
        {
            server.print();
        });
        std::cout << std::endl;
    }

    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
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
    std::cout << "current step: " << currentStep_ << std::endl;
    SystemState state = states_[currentStep_];
    ui->clientLabel->setText("empty");
    ui->bufferLabel->setText("empty");

    foreach(QLabel *label, ui->verticalLayoutWidget->findChildren<QLabel*>())
    {
        label->setText("empty");
    }

    if(!state.clients_[0].isFree())
    {
        Request request = state.clients_[0].retrieveRequest();
        QString clientText = QString::fromStdString(request.getRequestName());
        ui->clientLabel->setText(clientText);
    }

    if (!state.buffer_.isEmpty())
    {
        Request request = state.buffer_.getRequest();
        ui->bufferLabel->setText(QString::fromStdString(request.getRequestName()));
    }

    if (!state.servers_[0].isFree())
    {
        Request request = state.servers_[0].retrieveRequest();
        QString serverText = QString::fromStdString(request.getRequestName());

        QString name = QString::fromStdString(state.servers_[0].getServerName());
        QLabel * label = ui->verticalLayoutWidget->findChild<QLabel*>(name);

        label->setText(serverText);
    }

    if(currentStep_ < states_.size()-1)
    {
        ++currentStep_;
    }
    else
    {
        ui->nextStepButton->setEnabled(false);
    }

}

void StepModeWindow::on_nextStepButton_clicked()
{
    goToNextStep();
}
