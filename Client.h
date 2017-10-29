#ifndef CLIENT_H
#define CLIENT_H

#include "Request.h"

class Client
{
public:
    Client();
    Client(int clientNumber);
    void generateRequest(double currentTime);
    Request getRequest() const;
    Request request_;
private:
    int clientNumber_;
    int testInc_;
};

#endif // CLIENT_H
