#ifndef COMPONENT_H
#define COMPONENT_H

#include "Request.h"
#include <iosfwd>
#include <string>

class Component
{
public:
    Component();
    Component(int indexNumber);

    Request retrieveRequest();

    int getIndex() const;
    bool isFree() const;
    void print() const;

    friend std::ostream& operator<<(std::ostream & stream, const Component & component);
protected:
    Request request_;
    int indexNumber_;
    bool isFree_;
    std::string name_;
};

#endif // COMPONENT_H
