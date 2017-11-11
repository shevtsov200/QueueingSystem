#include "Manager.h"
#include "Request.h"
#include "Buffer.h"
#include "Server.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <iomanip>

Manager::Manager()
{
    currentTime_ = 0;
    numberOfGeneratedRequests_ = 0;
}

void Manager::start()
{
    const int requestsNumber = 100;
    const int bufferSize = 3;
    const int clientNumber = 4;
    const int serverNumber = 2;

    runSimulation(clientNumber, bufferSize, serverNumber, requestsNumber);

    std::vector<int> allRequestsNumber;
    std::vector<double> rejectProbabilities,
            systemStayMeans, bufferStayMeans, serviceStayMeans,
            bufferVariances, serviceVariances;
    std::vector<Request> allRequests;
    allRequests.insert(allRequests.begin(),rejectedRequests_.begin(),rejectedRequests_.end());
    allRequests.insert(allRequests.begin(),servicedRequests_.begin(),servicedRequests_.end());

    for(std::size_t i = 0; i < clientNumber; ++i)
    {
        std::vector<Request> clientAllRequests;
        std::copy_if(allRequests.cbegin(), allRequests.cend(), std::back_inserter(clientAllRequests),
                     [=](const Request & request)
        {
            return (request.getClientNumber() == i);
        });

        int rejectedRequestsNumber = std::count_if(rejectedRequests_.cbegin(),rejectedRequests_.cend(),
                                                   [=](const Request & request)
        {
            return (request.getClientNumber() == i);
        });
        int servicedRequestsNumber = std::count_if(servicedRequests_.cbegin(),servicedRequests_.cend(),
                                                   [=](const Request & request)
        {
            return (request.getClientNumber() == i);
        });


        int clientRequestsNumber = clientAllRequests.size();

        allRequestsNumber.push_back(clientRequestsNumber);

        double rejectProbability = double(rejectedRequestsNumber) / double(clientRequestsNumber);
        rejectProbabilities.push_back(rejectProbability);

        std::vector<double> bufferStayTimes;
        std::transform(clientAllRequests.cbegin(), clientAllRequests.cend(), std::back_inserter(bufferStayTimes),
                       [](const Request & request)
        {
            if(request.getServiceStartTime() != 0)
            {
                return (request.getServiceStartTime() - request.getCreationTime());
            }
            else
            {
                return (request.getEndTime() - request.getCreationTime());
            }

        });
        double bufferMean = calculateMean(bufferStayTimes);
        bufferStayMeans.push_back(bufferMean);
        double bufferVariance = calculateVariance(bufferStayTimes);
        bufferVariances.push_back(bufferVariance);

        std::vector<double> serviceStayTimes;
        std::transform(clientAllRequests.cbegin(), clientAllRequests.cend(), std::back_inserter(serviceStayTimes),
                       [](const Request & request)
        {
            if (request.getServiceStartTime() != 0)
            {
                return (request.getEndTime() - request.getServiceStartTime());
            }
            else
            {
                return 0.0;
            }
        });
        double serviceMean = calculateMean(serviceStayTimes);
        double serviceVariance = calculateVariance(serviceStayTimes);
        serviceStayMeans.push_back(serviceMean);
        serviceVariances.push_back(serviceVariance);

        double systemStayMean = bufferMean + serviceMean;
        systemStayMeans.push_back(systemStayMean);
    }

    const int spacingNumber = 13;
    std::cout << '|' << std::setw(spacingNumber) << "client"
              << '|' << std::setw(spacingNumber) << "requestNumber"
              << '|' << std::setw(spacingNumber) << "p_reject"
              << '|' << std::setw(spacingNumber) << "T_sys"
              << '|' << std::setw(spacingNumber) << "T_buf"
              << '|' << std::setw(spacingNumber) << "T_serv"
              << '|' << std::setw(spacingNumber) << "V_buf"
              << '|' << std::setw(spacingNumber) << "V_serv"
              << '|' << std::endl;
    for(std::size_t i = 0; i < clients_.size(); ++i)
    {
        std::cout << '|' << std::setw(spacingNumber) << clients_[i].getIndex()
                  << '|' << std::setw(spacingNumber) << allRequestsNumber[i]
                  << '|' << std::setw(spacingNumber) << rejectProbabilities[i]
                  << '|' << std::setw(spacingNumber) << systemStayMeans[i]
                  << '|' << std::setw(spacingNumber) << bufferStayMeans[i]
                  << '|' << std::setw(spacingNumber) << serviceStayMeans[i]
                  << '|' << std::setw(spacingNumber) << bufferVariances[i]
                  << '|' << std::setw(spacingNumber) << serviceVariances[i]
                  << '|' << std::endl;
    }
}

void Manager::runSimulation(int clientNumber, int bufferSize, int serverNumber, int requestsNumber)
{
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

        if(numberOfGeneratedRequests_ < requestsNumber)
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
    servicedRequest.setServiceStartTime(serverIt->getServiceStartTime());
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

double Manager::calculateVariance(const std::vector<double> & values) const
{
    double mean = calculateMean(values);
    double squareSum = std::inner_product(values.cbegin(), values.cend(),
                                          values.cbegin(),0.0);
    double variance = squareSum/values.size() - mean*mean;
    return variance;
}

double Manager::calculateMean(const std::vector<double> & values) const
{
    double sum = std::accumulate(values.cbegin(),values.cend(),0.0);
    double mean = sum / values.size();
    return mean;
}
