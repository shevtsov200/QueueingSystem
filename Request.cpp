#include "Request.h"
#include <iostream>


Request::Request()
{
    creationTime_ = 0;
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

double Request::getEndTime() const
{
    return endTime_;
}

int Request::getRequestNumber() const
{
    return requestNumber_;
}

void Request::setEndTime(double endTime)
{
    endTime_ = endTime;
}

std::ostream& operator<<(std::ostream & stream, const Request & request)
{
    return stream << "request"<<"("<<request.clientNumber_<<","<<request.requestNumber_<<")";
}
