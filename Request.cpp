#include "Request.h"
#include <iostream>
#include <sstream>

Request::Request()
{
    creationTime_ = 0;
    serviceStartTime_ = 0;
    endTime_ = 0;
    clientNumber_ = 0;
    requestNumber_ = 0;
}

Request::Request(double creationTime, int clientNumber, int requestNumber) : Request()
{
    creationTime_ = creationTime;
    clientNumber_ = clientNumber;
    requestNumber_ = requestNumber;
}

double Request::getCreationTime() const
{
    return creationTime_;
}

double Request::getServiceStartTime() const
{
    return serviceStartTime_;
}

double Request::getEndTime() const
{
    return endTime_;
}

int Request::getRequestNumber() const
{
    return requestNumber_;
}

int Request::getClientNumber() const
{
    return clientNumber_;
}

void Request::setServiceStartTime(double serviceStartTime)
{
    serviceStartTime_ = serviceStartTime;
}

void Request::setEndTime(double endTime)
{
    endTime_ = endTime;
}

std::string Request::getRequestName() const
{
    std::stringstream stream;
    stream << "request"<<"("<<clientNumber_<<","<<requestNumber_<<")";
    return stream.str();
}

std::ostream& operator<<(std::ostream & stream, const Request & request)
{
    return stream << request.getRequestName();
}
