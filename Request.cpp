#include "Request.h"

Request::Request()
{
    creationTime_ = 0;
    endTime_ = 0;
}

Request::Request(double creationTime)
{
    creationTime_ = creationTime;
    endTime_ = 0;
}

double Request::getCreationTime() const
{
    return creationTime_;
}

double Request::getEndTime() const
{
    return endTime_;
}

void Request::setEndTime(double endTime)
{
    endTime_ = endTime;
}
