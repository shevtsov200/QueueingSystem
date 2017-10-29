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
    const int clientNumber = 2;
    const int serverNumber = 1;

    for (int i = 0; i < clientNumber; ++i)
    {
        Client client = Client(i);
        clients_.push_back(client);
    }

    buffer_ = Buffer(bufferSize);

    for (int i = 0; i < serverNumber; ++i)
    {
        Server server = Server();
        servers_.push_back(server);
    }

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

        if (serverIt->isFree())
        {
            Request request = buffer_.getRequest();
            std::cout << "send " << request << " to server." << std::endl;
            serverIt->serveRequest(currentTime_,request);
            std::cout << "Server will be free at " << serverIt->getServiceFinishTime() << std::endl;
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

void Manager::sendRequestToServer(Request & request)
{
    /*if (server_.isFree())
    {
        std::cout << "send " << request << " to server." << std::endl;
        server_.serveRequest(currentTime_,request);
    }*/
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
