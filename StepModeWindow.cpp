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
        QString name = QString::fromStdString(states_.back().servers_[i].getServerName());
        initializeLabel(label,name);
        ui->verticalLayout->addWidget(label);
    }

    for(std::size_t i = 0; i < states_.back().buffer_.getSize(); ++i)
    {
        QLabel *label = new QLabel();
        QString name = QString("buffer"+i);
        initializeLabel(label,name);
        ui->verticalLayout_2->addWidget(label);
    }

    ui->clientLabel->setText("empty");
    //ui->bufferLabel->setText("empty");

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
    //ui->bufferLabel->setText("empty");

    foreach(QLabel *label, ui->verticalLayoutWidget->findChildren<QLabel*>())
    {
        label->setText("empty");
    }

    foreach(QLabel *label, ui->verticalLayoutWidget_2->findChildren<QLabel*>())
    {
        label->setText("empty");
    }

    if(!state.clients_[0].isFree())
    {
        Request request = state.clients_[0].retrieveRequest();
        QString clientText = QString::fromStdString(request.getRequestName());
        ui->clientLabel->setText(clientText);
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
            //ui->bufferLabel->setText(QString::fromStdString(request.getRequestName()));
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
    label->setText("empty");
    label->setMinimumWidth(100);
    label->setMinimumHeight(50);
    label->setObjectName(name);
}

void StepModeWindow::on_nextStepButton_clicked()
{
    goToNextStep();
}
