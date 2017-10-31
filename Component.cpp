#include "Component.h"
#include <iostream>

Component::Component()
{
    indexNumber_ = 0;
    isFree_ = true;
}

Component::Component(int indexNumber) : Component()
{
    indexNumber_ = indexNumber;
}

Request Component::retrieveRequest()
{
    isFree_ = true;
    return request_;
}

int Component::getIndex() const
{
    return indexNumber_;
}

bool Component::isFree() const
{
    return isFree_;
}
