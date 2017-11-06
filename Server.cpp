#include "Server.h"
#include "Request.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>

Server::Server()
{
    serviceStartTime_ = 0;
    serviceFinishTime_ = 0;
}

Server::Server(int indexNumber) : Server()
{
    indexNumber_ = indexNumber;
}

void Server::serveRequest(double currentTime, const Request & request)
{
    const int lambda = 1;
    double serviceDuration = (log(std::rand() + 1) - log(RAND_MAX)) / (-lambda);
    request_ = request;
    serviceStartTime_ = currentTime;
    serviceFinishTime_ = serviceStartTime_ + serviceDuration;

    isFree_ = false;
}

double Server::getServiceStartTime() const
{
    return serviceStartTime_;
}

double Server::getServiceFinishTime() const
{
    return serviceFinishTime_;
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
    return stream << "server" << server.getIndex();
}
