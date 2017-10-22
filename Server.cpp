#include "Server.h"
#include "Request.h"
#include <cstdlib>
#include <cmath>

Server::Server()
{
    isFree_ = true;
}

void Server::serveRequest(double currentTime, const Request & request)
{
    const int lambda = 5;
    double serviceDuration = (log(std::rand() + 1) - log(RAND_MAX)) / (-lambda);
    request_ = request;
    serviceFinishTime_ = currentTime + serviceDuration;

    isFree_ = false;
}

bool Server::isFree() const
{
    return isFree_;
}
