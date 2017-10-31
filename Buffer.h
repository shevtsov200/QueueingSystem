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
    Request getRequest();
    Request removeOldestRequest();
    void print() const;
private:
    int bufferSize_;
    std::vector<Request> requests_;
};

#endif // BUFFER_H
