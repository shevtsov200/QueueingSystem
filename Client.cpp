#include "Client.h"
#include "Request.h"
#include <cstdlib>
#include <iostream>

Client::Client()
{
    testInc_ = 0;
    a_ = 0;
    b_ = 1;
}

Client::Client(int indexNumber, double a, double b) : Client()
{
    indexNumber_ = indexNumber;
    a_ = a;
    b_ = b;
}

void Client::generateRequest(double currentTime)
{

    double creationTime = currentTime + (((double)std::rand() / (double)RAND_MAX) * (b_ - a_) + a_);
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
