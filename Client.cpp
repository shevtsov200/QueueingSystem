#include "Client.h"
#include "Request.h"
#include <cstdlib>
#include <iostream>

Client::Client()
{
    clientNumber_ = 0;
    testInc_ = 0;
}

Client::Client(int clientNumber) : Client()
{
    clientNumber_ = clientNumber;
}

void Client::generateRequest(double currentTime)
{
    const double a = 0;
    const double b = 1;
    double creationTime = currentTime + (((double)std::rand() / (double)RAND_MAX) * (b - a) + a);
    Request request = Request(creationTime, clientNumber_, testInc_++);
    request_ = request;
}

Request Client::getRequest() const
{
    return request_;
}

int Client::getClientNumber() const
{
    return clientNumber_;
}

std::ostream &operator<<(std::ostream &stream, const Client &client)
{
    return stream << "client" << client.getClientNumber();
}
