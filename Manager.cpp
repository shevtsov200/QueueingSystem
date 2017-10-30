#include "Manager.h"
#include "Request.h"
#include "Buffer.h"
#include "Server.h"
#include <iostream>
#include <algorithm>

Manager::Manager()
{

}

void Manager::start()
{
    const double step = 0.5;
    const double endTime = 5;
    const int bufferSize = 3;
    const int clientNumber = 2;
    const int serverNumber = 2;

    for (int i = 0; i < clientNumber; ++i)
    {
        Client client = Client(i);
        clients_.push_back(client);
    }

    buffer_ = Buffer(bufferSize);

    for (int i = 0; i < serverNumber; ++i)
    {
        Server server = Server(i);
        servers_.push_back(server);
    }
    nextServer_ = servers_.begin();

    for (std::vector<Client>::iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
        it->generateRequest(currentTime_);
        std::cout << "initial generation: " << it->request_ << " " << it->request_.getCreationTime() << std::endl;
    }

    while(currentTime_ < endTime)
    {
        std::cout << "------------------------------" << std::endl;

        std::vector<Client>::iterator clientIt = getEarliestClient();
        std::vector<Server>::iterator serverIt = getEarliestServer();

        Request request = clientIt->getRequest();
        std::cout << "get " << request << " created at " << request.getCreationTime() << std::endl;

        if (currentTime_ < request.getCreationTime())
        {
            currentTime_ = request.getCreationTime();
        }

        if ((currentTime_ > serverIt->getServiceFinishTime()) && !serverIt->isFree())
        {
            currentTime_ = serverIt->getServiceFinishTime();
            Request servicedRequest = serverIt->retrieveServicedRequest();
            sendRequestToServiced(servicedRequest);
        }
        currentTime_ = request.getCreationTime();

        clientIt->generateRequest(currentTime_);

        sendRequestToBuffer(request);

        if (nextServer_->isFree())
        {
            Request request = buffer_.getRequest();
            std::cout << "send " << request << " to " << *nextServer_ << std::endl;
            nextServer_->serveRequest(currentTime_,request);
            std::cout << *nextServer_ << " will be free at " << nextServer_->getServiceFinishTime() << std::endl;
            moveNextServer();
        }
        else
        {
            moveNextServer();
        }

        std::cout << "------------------------------" << std::endl;
    }
}

void Manager::rejectRequest(Request & request)
{
    request.setEndTime(currentTime_);
    rejectedRequests_.push_back(request);
    std::cout << "reject " << request << std::endl;
}

void Manager::sendRequestToServiced(Request &request)
{
    request.setEndTime(currentTime_);
    servicedRequests_.push_back(request);
    std::cout <<"Send " << request << " to serviced" << std::endl;
}

void Manager::sendRequestToBuffer(Request & request)
{
    if (!buffer_.isFree())
    {
        Request oldestRequest = buffer_.removeOldestRequest();
        rejectRequest(oldestRequest);
    }
    buffer_.addRequest(request);
    std::cout << "Put " << request << " to the buffer." << std::endl;
}

std::vector<Client>::iterator Manager::getEarliestClient()
{
    return std::min_element(clients_.begin(), clients_.end(),
                                                                [](const Client & left, const Client & right)
            {
                return (left.request_.getCreationTime() < right.request_.getCreationTime());
    });
}

std::vector<Server>::iterator Manager::getEarliestServer()
{
    return std::min_element(servers_.begin(), servers_.end(),
                                                                [](const Server & left, const Server & right)
            {
                return (left.getServiceFinishTime() < right.getServiceFinishTime());
    });
}
/*
void Manager::findFreeServer()
{
    std::vector<Server>::iterator oldIt = nextServer_;
    moveNextServer();
    while(nextServer_ != oldIt)
    {
        moveNextServer();
        if(nextServer_ )
    }

}*/

void Manager::moveNextServer()
{
    ++nextServer_;
    if(nextServer_ == servers_.end())
    {
        nextServer_ = servers_.begin();
    }
}
