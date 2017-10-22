#include <iostream>
#include "Manager.h"
#include "Request.h"
#include "Buffer.h"
#include "Server.h"

Manager::Manager()
{

}

void Manager::start()
{
    const double step = 0.5;
    const double endTime = 5;
    const int bufferSize = 3;

    client_ = Client();
    buffer_ = Buffer(bufferSize);
    server_ = Server();

    for(double currentTime = 0; currentTime < endTime; currentTime += step)
    {
        currentTime_ = currentTime;
        std::cout << "------------------------------" << std::endl;
        std::cout << "currentTime = " << currentTime << std::endl;

        Request request = client_.generateRequest(currentTime);
        std::cout << "generate request at " << request.getCreationTime() << std::endl;

        sendRequestToBuffer(request);

        request = buffer_.getRequest();

        sendRequestToServer(request);

        std::cout << "------------------------------" << std::endl << std::endl;
    }
}

void Manager::rejectRequest(Request & request)
{
    request.setEndTime(currentTime_);
    rejectedRequests_.push_back(request);
    std::cout << "reject request" << std::endl;
}

void Manager::sendRequestToBuffer(Request & request)
{
    if (buffer_.isFree())
    {
        buffer_.addRequest(request);
    }
    else
    {
        rejectRequest(request);
    }
}

void Manager::sendRequestToServer(Request & request)
{
    if (server_.isFree())
    {
        server_.serveRequest(currentTime_,request);
    }
    else
    {
        rejectRequest(request);
    }
}
