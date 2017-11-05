#include "Manager.h"
#include "Request.h"
#include "Buffer.h"
#include "Server.h"
#include <iostream>
#include <algorithm>

Manager::Manager()
{
    currentTime_ = 0;
    numberOfGeneratedRequests_ = 0;
}

void Manager::start()
{
    const double step = 0.5;
    const int N = 4;
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
    }

    while((numberOfGeneratedRequests_ < N) || requestsLeftInSystem())
    {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "currentTime " << currentTime_ << std::endl;

        std::vector<Client>::iterator clientIt = getEarliestClient();
        std::vector<Server>::iterator serverIt = getEarliestServer();

        if(serverIt != servers_.end())
        {
            if ((currentTime_ >= serverIt->getServiceFinishTime()) && !serverIt->isFree())
            {
                sendRequestToServiced(serverIt);
            }
        }

        if (clientIt != clients_.end())
        {
            if(!clientIt->isFree())
            {
                Request request = clientIt->retrieveRequest();
                std::cout << *clientIt << " -> " << request << " time: " << currentTime_ << std::endl;
                sendRequestToBuffer(request);
            }
        }
        else
        {
            std::vector<Server>::iterator serverIt = getEarliestServer();
            if(serverIt != servers_.end())
            {
                currentTime_ = serverIt->getServiceFinishTime();
            }
        }

        if(numberOfGeneratedRequests_ < N)
        {
            clientIt->generateRequest(currentTime_);
            currentTime_ = clientIt->getRequestCreationTime();
            ++numberOfGeneratedRequests_;
        }


        if(!buffer_.isEmpty())
        {
            sendRequestToServer();
        }

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

void Manager::sendRequestToServiced(std::vector<Server>::iterator serverIt)
{
    Request servicedRequest = serverIt->retrieveRequest();
    servicedRequest.setEndTime(serverIt->getServiceFinishTime());
    servicedRequests_.push_back(servicedRequest);
    std::cout << servicedRequest << "-> serviced" << " time: " << servicedRequest.getEndTime() <<  std::endl;
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
    for(std::vector<Client>::iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
        std::vector<Client>::iterator minIt = std::min_element(it, clients_.end(),
                                                         []( Client & left,  Client & right)
        {
            return (left.getRequestCreationTime() < right.getRequestCreationTime());
        });
        if (!minIt->isFree())
        {
            return minIt;
        }
    }
    return clients_.end();
}

std::vector<Server>::iterator Manager::getEarliestServer()
{
    std::vector<Server>::iterator bound = std::partition(servers_.begin(),servers_.end(),
                                                      [](Server & server)
    {
            return !server.isFree();
    });
    std::vector<Server>::iterator minIt = std::min_element(servers_.begin(), bound,
                                                     []( Server & left,  Server & right)
    {
        return (left.getServiceFinishTime() < right.getServiceFinishTime());
    });
    return minIt;
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

bool Manager::requestsLeftInSystem() const
{
    bool serversEmpty = (std::find_if_not(servers_.cbegin(),servers_.cend(),
                                        [](const Server & server)
    {
        return server.isFree();
    }) == servers_.cend());


    return (!serversEmpty || !buffer_.isEmpty());
}
