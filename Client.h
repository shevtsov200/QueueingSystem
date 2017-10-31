#ifndef CLIENT_H
#define CLIENT_H

#include "Request.h"
#include <iosfwd>

class Client
{
public:
    Client();
    Client(int clientNumber);
    void generateRequest(double currentTime);
    Request getRequest() const;
    int getClientNumber() const;
    friend std::ostream &operator<<(std::ostream &stream, const Client &client);
    Request request_;
private:
    int clientNumber_;
    int testInc_;
};

#endif // CLIENT_H
