#ifndef MANAGER_H
#define MANAGER_H

#include "Client.h"
#include "Buffer.h"
#include "Server.h"
#include "Request.h"
#include <vector>

class Manager
{
public:
    Manager();
    void start();
private:
    Client client_;
    Buffer buffer_;
    Server server_;

    std::vector<Request> servicedRequests_;
    std::vector<Request> rejectedRequests_;

    double currentTime_;

    void rejectRequest(Request & request);
    void sendRequestToBuffer(Request & request);
    void sendRequestToServer(Request & request);
};

#endif // MANAGER_H
