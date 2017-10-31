#include "Server.h"
#include "Request.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>

Server::Server()
{
    isFree_ = true;
    serverNumber_ = 0;
    serviceFinishTime_ = 0;
}

Server::Server(int serverNumber)
{
    isFree_ = true;
    serverNumber_ = serverNumber;
    serviceFinishTime_ = 0;
}

void Server::serveRequest(double currentTime, const Request & request)
{
    const int lambda = 1;
    double serviceDuration = (log(std::rand() + 1) - log(RAND_MAX)) / (-lambda);
    request_ = request;
    serviceFinishTime_ = currentTime + serviceDuration;

    isFree_ = false;
}

Request Server::retrieveServicedRequest()
{
    isFree_ = true;
    return request_;
}

bool Server::isFree() const
{
    return isFree_;
}

double Server::getServiceFinishTime() const
{
    return serviceFinishTime_;
}

int Server::getServerNumber() const
{
    return serverNumber_;
}

void Server::print() const
{
    std::cout << *this << ":" << "|";
    if (!isFree_)
    {
        std::cout << request_ << "| until " << getServiceFinishTime();
    }
    else
    {
        std::cout << std::string(12,'*') << "|";
    }
    std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &stream, const Server &server)
{
    return stream << "server" << server.getServerNumber();
}
