#include "Buffer.h"
#include "Request.h"
#include <algorithm>

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

Request Buffer::removeOldestRequest()
{
    std::vector<Request>::iterator it = std::min_element(requests_.begin(),requests_.end(),
                                       [](const Request & left, const Request & right)
    {
        return (left.getCreationTime() < right.getCreationTime());
    });
    Request request = *it;
    requests_.erase(it);
    return request;
}
