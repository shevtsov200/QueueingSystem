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
    std::vector<Client> clients_;
    Buffer buffer_;
    std::vector<Server> servers_;
    std::vector<Server>::iterator nextServer_;

    std::vector<Request> servicedRequests_;
    std::vector<Request> rejectedRequests_;

    double currentTime_;

    std::vector<Client>::iterator getEarliestClient();
    std::vector<Server>::iterator getEarliestServer();
    void rejectRequest(Request & request);
    void sendRequestToServiced(Request & request);
    void sendRequestToBuffer(Request & request);
    void sendRequestToServer();

    void moveNextServer();

    void printComponents() const;
};

#endif // MANAGER_H
