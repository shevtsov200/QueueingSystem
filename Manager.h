#ifndef MANAGER_H
#define MANAGER_H

#include "Client.h"
#include "Buffer.h"
#include "Server.h"
#include "Request.h"
#include "Statistics.h"
#include "SystemState.h"

#include <vector>
#include <functional>

class Manager
{
public:
    Manager();
    Statistics start(int requestsNumber, int bufferSize, int clientCount, int serverCount, double a, double b, double lambda);
    void runSimulation(int requestsNumber, int bufferSize, int clientCount, int serverCount, double a, double b, double lambda);

    const std::vector<SystemState> getStates() const;
private:
    std::vector<Client> clients_;
    Buffer buffer_;
    std::vector<Server> servers_;
    std::vector<Server>::iterator nextServer_;

    std::vector<Request> servicedRequests_;
    std::vector<Request> rejectedRequests_;
    int numberOfGeneratedRequests_;

    std::vector<SystemState> states_;

    double currentTime_;
    double executionTime_;

    std::vector<Client>::iterator getEarliestClient();
    std::vector<Server>::iterator getEarliestServer();
    void rejectRequest(Request & request);
    void sendRequestToServiced(std::vector<Server>::iterator serverIt);
    void sendRequestToBuffer(Request & request);
    void sendRequestToServer();

    std::vector<Server>::iterator moveRingIt(std::vector<Server>::iterator it);

    void printComponents() const;
    void saveState();
    bool requestsLeftInSystem() const;
};

#endif // MANAGER_H
