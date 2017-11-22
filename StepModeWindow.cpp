#include "StepModeWindow.h"
#include "ui_StepModeWindow.h"

#include "SystemState.h"
#include "Manager.h"

#include <vector>
#include <iostream>
#include <string>

void StepModeWindow::startStepMode(int requestsCount, int bufferSize, int clientCount, double serverCount, double a, double b, double lambda)
{
    Manager manager = Manager();
    manager.start(requestsCount, bufferSize, clientCount, serverCount, a, b, lambda);

    states_ = manager.getStates();
    currentStep_ = 0;

    for(std::size_t i = 0; i < states_.back().clients_.size(); ++i)
    {
        QLabel *label = new QLabel();
        QString name = QString::fromStdString(states_.back().clients_[i].getClientName());
        initializeLabel(label,name);
        ui->verticalLayout_3->addWidget(label);
    }

    for(std::size_t i = 0; i < states_.back().buffer_.getSize(); ++i)
    {
        QLabel *label = new QLabel();
        QString name = QString("buffer"+i);
        initializeLabel(label,name);
        ui->verticalLayout_2->addWidget(label);
    }

    for(std::size_t i = 0; i < states_.back().servers_.size(); ++i)
    {
        QLabel *label = new QLabel();
        QString name = QString::fromStdString(states_.back().servers_[i].getServerName());
        initializeLabel(label,name);
        ui->verticalLayout->addWidget(label);
    }

    ui->servicedLabel->setText(EMPTY_TEXT);
    ui->rejectedLabel->setText(EMPTY_TEXT);
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
    printCurrentState();
    SystemState state = states_[currentStep_];

    foreach(QLabel *label, ui->verticalLayoutWidget->findChildren<QLabel*>())
    {
        label->setText(EMPTY_TEXT);
    }

    foreach(QLabel *label, ui->verticalLayoutWidget_2->findChildren<QLabel*>())
    {
        label->setText(EMPTY_TEXT);
    }

    foreach(QLabel *label, ui->verticalLayoutWidget_3->findChildren<QLabel*>())
    {
        label->setText(EMPTY_TEXT);
    }

    ui->rejectedLabel->setText(EMPTY_TEXT);
    ui->servicedLabel->setText(EMPTY_TEXT);

    for(std::size_t i = 0; i < state.clients_.size(); ++i)
    {
        if(i == state.generatingClientIndex_)
        {
            Request request = state.clients_[i].retrieveRequest();
            QString name = QString::fromStdString(state.clients_[i].getClientName());
            QString clientText = QString::fromStdString(request.getRequestName());

            QLabel * label = ui->verticalLayoutWidget_3->findChild<QLabel*>(name);
            label->setText(clientText);
        }
    }

    for(std::size_t i = 0; i < state.buffer_.getSize(); ++i)
    {
        if (!state.buffer_.isEmpty())
        {
            Request request = state.buffer_.getRequest();

            QString bufferText = QString::fromStdString(request.getRequestName());

            QString name = QString::fromStdString("buffer"+i);
            QLabel * label = ui->verticalLayoutWidget_2->findChild<QLabel*>(name);
            label->setText(bufferText);
        }
    }

    for(auto it = state.servers_.begin(); it != state.servers_.end(); ++it)
    {
        if(!it->isFree())
        {
            Request request = it->retrieveRequest();
            QString serverText = QString::fromStdString(request.getRequestName());

            QString name = QString::fromStdString(it->getServerName());
            QLabel * label = ui->verticalLayoutWidget->findChild<QLabel*>(name);

            label->setText(serverText);
        }
    }

    if(!state.serviced_.empty())
    {
        Request request = state.serviced_.back();
        QString servicedText = QString::fromStdString(request.getRequestName());

        ui->servicedLabel->setText(servicedText);
    }

    if(!state.rejected_.empty())
    {
        Request request = state.rejected_.back();
        QString rejectedText = QString::fromStdString(request.getRequestName());

        ui->rejectedLabel->setText(rejectedText);
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

void StepModeWindow::initializeLabel(QLabel *label, QString name)
{
    label->setText(EMPTY_TEXT);
    label->setMinimumWidth(100);
    label->setMinimumHeight(50);
    label->setObjectName(name);
}

void StepModeWindow::printCurrentState()
{
    std::cout << "-------------------------------------" << std::endl;
    std::size_t i = currentStep_;
    states_[i].buffer_.print();
    std::for_each(states_[i].servers_.begin(),states_[i].servers_.end(),
                  [](const Server & server)
    {
        server.print();
    });
    std::cout << std::endl;

    std::cout << "-------------------------------------" << std::endl;
}

void StepModeWindow::on_nextStepButton_clicked()
{
    goToNextStep();
}

void StepModeWindow::on_backButton_clicked()
{
    emit changeStackedWidgetIndex(3);
}
