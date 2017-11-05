#include "Client.h"
#include "Request.h"
#include <cstdlib>
#include <iostream>

Client::Client()
{
    testInc_ = 0;
}

Client::Client(int indexNumber) : Client()
{
    indexNumber_ = indexNumber;
}

void Client::generateRequest(double currentTime)
{
    const double a = 0;
    const double b = 1;
    double creationTime = currentTime + (((double)std::rand() / (double)RAND_MAX) * (b - a) + a);
    Request request = Request(creationTime, indexNumber_, testInc_++);
    request_ = request;
    isFree_ = false;
}

double Client::getRequestCreationTime() const
{
    return request_.getCreationTime();
}

std::ostream &operator<<(std::ostream &stream, const Client &client)
{
    return stream << "client" << client.getIndex();
}
