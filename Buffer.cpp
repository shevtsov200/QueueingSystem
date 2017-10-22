#include "Buffer.h"
#include "Request.h"


Buffer::Buffer()
{
    bufferSize_ = 0;
}

Buffer::Buffer(int bufferSize)
{
    bufferSize_ = bufferSize;
}

bool Buffer::isFree() const
{
    return (requests_.size() < bufferSize_);
}

void Buffer::addRequest(const Request & request)
{
    requests_.push_back(request);
}

Request Buffer::getRequest()
{
    Request request = requests_.back();
    requests_.pop_back();
    return request;
}
