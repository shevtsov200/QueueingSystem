#include "Server.h"
#include "Request.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Server::Server()
{
    isFree_ = true;
    serverNumber_ = 0;
}

Server::Server(int serverNumber)
{
    isFree_ = true;
    serverNumber_ = serverNumber;
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

std::ostream &operator<<(std::ostream &stream, const Server &server)
{
    return stream << "server" << server.getServerNumber();
}
