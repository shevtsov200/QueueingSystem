#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include "Request.h"

class Buffer
{
public:
    Buffer();
    Buffer(int buffersize);
    void addRequest(const Request & request);
    bool isFree() const;
    bool isEmpty() const;
    Request getRequest();
    Request removeOldestRequest();
    void print() const;
    std::size_t getSize() const;
    Request requestAt(std::size_t index);
private:
    std::size_t bufferSize_;
    std::vector<Request> requests_;
};

#endif // BUFFER_H
