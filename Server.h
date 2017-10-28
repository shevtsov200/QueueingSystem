#ifndef SERVER_H
#define SERVER_H

#include "Request.h"

class Server
{
public:
    Server();
    void serveRequest(double currentTime, const Request & request);
    Request retrieveServicedRequest();
    bool isFree() const;
    double getServiceFinishTime() const;
private:
    Request request_;
    double serviceFinishTime_;
    bool isFree_;
};

#endif // SERVER_H
