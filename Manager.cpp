#include "Manager.h"
#include "Request.h"
#include "Buffer.h"
#include "Server.h"
#include "Statistics.h"

#include <iostream>
#include <algorithm>
#include <functional>

Manager::Manager()
{
    currentTime_ = 0;
    executionTime_ = 0;
    numberOfGeneratedRequests_ = 0;
}

Statistics Manager::start(int requestsNumber, int bufferSize, int clientCount, int serverCount, double a, double b, double lambda)
{
    runSimulation(requestsNumber, bufferSize, clientCount, serverCount, a, b, lambda);

    Statistics statistics = Statistics(clients_, rejectedRequests_,servicedRequests_, servers_, executionTime_);
    statistics.calculateStatistics();

    statistics.printClientTable();
    std::cout << std::endl;
    statistics.printServerTable();

    return statistics;
}

void Manager::runSimulation(int requestsNumber, int bufferSize, int clientCount, int serverCount, double a, double b, double lambda)
{
    for (int i = 0; i < clientCount; ++i)
    {
        Client client = Client(i,a,b);
        clients_.push_back(client);
    }

    buffer_ = Buffer(bufferSize);

    for (int i = 0; i < serverCount; ++i)
    {
        Server server = Server(i,lambda);
        servers_.push_back(server);
    }
    nextServer_ = servers_.begin();

    for (std::vector<Client>::iterator it = clients_.begin(); it != clients_.end(); ++it)
    {
        it->generateRequest(currentTime_);
    }

    while((numberOfGeneratedRequests_ < requestsNumber) || requestsLeftInSystem())
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
                if(numberOfGeneratedRequests_ < requestsNumber)
                {
                    Request request = clientIt->retrieveRequest();

                    saveState();
                    states_.back().generatingClientIndex_ = std::distance(clients_.begin(),clientIt);

                    numberOfGeneratedRequests_++;
                    currentTime_ = request.getCreationTime();
                    std::cout << *clientIt << " -> " << request << " time: " << currentTime_ << std::endl;

                    sendRequestToBuffer(request);
                }
            }
        }

        if ((clientIt == clients_.end()) || (numberOfGeneratedRequests_ >= requestsNumber))
        {
            std::vector<Server>::iterator serverIt = getEarliestServer();
            if(serverIt != servers_.end())
            {
                currentTime_ = serverIt->getServiceFinishTime();
            }
        }

        clientIt->generateRequest(currentTime_);

        if(!buffer_.isEmpty())
        {
            sendRequestToServer();
        }

        std::cout << std::endl;
        printComponents();
        std::cout << "---------------------------------------------" << std::endl;
    }
}

const std::vector<SystemState> Manager::getStates() const
{
    return states_;
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
    servicedRequest.setServiceStartTime(serverIt->getServiceStartTime());
    servicedRequest.setEndTime(serverIt->getServiceFinishTime());
    servicedRequests_.push_back(servicedRequest);
    std::cout << servicedRequest << "-> serviced" << " time: " << servicedRequest.getEndTime() <<  std::endl;
    saveState();

    if(!requestsLeftInSystem())
    {
        executionTime_ = servicedRequest.getEndTime();
    }
}

void Manager::sendRequestToBuffer(Request & request)
{
    if (!buffer_.isFree())
    {
        Request oldestRequest = buffer_.removeOldestRequest();
        rejectRequest(oldestRequest);

        std::size_t i = states_.back().generatingClientIndex_;
        saveState();
        states_.back().generatingClientIndex_ = i;

    }
    buffer_.addRequest(request);
    std::cout << request << " -> buffer" << " time: " << currentTime_ <<  std::endl;
    saveState();
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
            saveState();
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
    std::vector<Server> serversCopy = servers_;
    std::vector<Server>::iterator bound = std::stable_partition(serversCopy.begin(),serversCopy.end(),
                                                                [](Server & server)
    {
            return !server.isFree();
});

    std::vector<Server>::iterator minItOfCopy = std::min_element(serversCopy.begin(), bound,
                                                                 []( Server & left,  Server & right)
    {
            return (left.getServiceFinishTime() < right.getServiceFinishTime());
});

    if(minItOfCopy == bound)
    {
        return servers_.end();
    }

    std::vector<Server>::iterator minIt =std::find_if(servers_.begin(), servers_.end(),
                                                      [&](Server & server)
    {
            return (server.getIndex() == minItOfCopy->getIndex());
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

void Manager::saveState()
{
    SystemState state(clients_, buffer_, servers_, rejectedRequests_, servicedRequests_);
    states_.push_back(state);
    std::cout << "new size: " << states_.size() << std::endl;
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
