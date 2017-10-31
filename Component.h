#ifndef COMPONENT_H
#define COMPONENT_H

#include "Request.h"

class Component
{
public:
    Component();
    Component(int indexNumber);

    Request retrieveRequest();

    int getIndex() const;
    bool isFree() const;

protected:
    Request request_;
    int indexNumber_;
    bool isFree_;
};

#endif // COMPONENT_H
