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
    allServiceTime_ = 0;
    lambda_ = 1;
}

Server::Server(int indexNumber, double lambda) : Server()
{
    indexNumber_ = indexNumber;
    lambda_ = lambda;
}

void Server::serveRequest(double currentTime, const Request & request)
{
    double serviceDuration = (log(std::rand() + 1) - log(RAND_MAX)) / (-lambda_);
    request_ = request;
    serviceStartTime_ = currentTime;
    serviceFinishTime_ = serviceStartTime_ + serviceDuration;
    allServiceTime_ += serviceDuration;

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

double Server::getAllServiceTime() const
{
    return allServiceTime_;
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
