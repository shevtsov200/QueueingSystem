#ifndef SERVER_H
#define SERVER_H

#include "Request.h"
#include <iosfwd>

class Server
{
public:
    Server();
    Server(int serverNumber);
    void serveRequest(double currentTime, const Request & request);
    Request retrieveServicedRequest();
    bool isFree() const;
    double getServiceFinishTime() const;
    int getServerNumber() const;
    void print() const;

    friend std::ostream& operator<<(std::ostream & stream, const Server & server);
private:
    Request request_;
    double serviceFinishTime_;
    bool isFree_;
    int serverNumber_;
};

#endif // SERVER_H
