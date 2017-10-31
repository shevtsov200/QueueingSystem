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
    const double endTime = 2;
    const int bufferSize = 3;
    const int clientNumber = 3;
    const int serverNumber = 3;

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
    }

    while(currentTime_ < endTime)
    {
        std::cout << "---------------------------------------------" << std::endl;


        std::vector<Client>::iterator clientIt = getEarliestClient();
        std::vector<Server>::iterator serverIt = getEarliestServer();

        Request request = clientIt->retrieveRequest();

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


        std::cout << *clientIt << " -> " << request << " time: " << currentTime_ << std::endl;

        clientIt->generateRequest(currentTime_);

        sendRequestToBuffer(request);
        sendRequestToServer();

        std::cout << std::endl;
        printComponents();

        std::cout << "---------------------------------------------" << std::endl;
    }
}

void Manager::rejectRequest(Request & request)
{
    request.setEndTime(currentTime_);
    rejectedRequests_.push_back(request);
    std::cout << request << "-> rejected" << " time: " << currentTime_ <<  std::endl;
}

void Manager::sendRequestToServiced(Request &request)
{
    request.setEndTime(currentTime_);
    servicedRequests_.push_back(request);
    std::cout << request << " -> serviced" << " time: " << currentTime_ <<  std::endl;
}

void Manager::sendRequestToBuffer(Request & request)
{
    if (!buffer_.isFree())
    {
        Request oldestRequest = buffer_.removeOldestRequest();
        rejectRequest(oldestRequest);
    }
    buffer_.addRequest(request);
    std::cout << request << " -> buffer" << " time: " << currentTime_ <<  std::endl;
}

void Manager::sendRequestToServer()
{
    std::vector<Server>::iterator initialIt = nextServer_;
    std::vector<Server>::iterator it = nextServer_;
    do
    {
        if (it->isFree())
        {
            nextServer_ = it;
            Request request = buffer_.getRequest();
            std::cout << request << " -> " << *nextServer_ << " time: " << currentTime_ <<  std::endl;
            nextServer_->serveRequest(currentTime_,request);
            break;
        }
        it = moveRingIt(it);
    }
    while(it != initialIt);
}

std::vector<Client>::iterator Manager::getEarliestClient()
{
    return std::min_element(clients_.begin(), clients_.end(),
                                                                [](const Client & left, const Client & right)
            {
                return (left.getRequestCreationTime() < right.getRequestCreationTime());
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

void Manager::moveNextServer()
{
    ++nextServer_;
    if(nextServer_ == servers_.end())
    {
        nextServer_ = servers_.begin();
    }
}

std::vector<Server>::iterator Manager::moveRingIt(std::vector<Server>::iterator it)
{
    ++it;
    if(it == servers_.end())
    {
        it = servers_.begin();
    }
    return it;
}

void Manager::printComponents() const
{
    buffer_.print();
    std::for_each(servers_.begin(),servers_.end(),
                  [](const Server & server)
    {
        server.print();
    });
}
