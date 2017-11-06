#ifndef SERVER_H
#define SERVER_H

#include "Request.h"
#include "Component.h"
#include <iosfwd>

class Server : public Component
{
public:
    Server();
    Server(int indexNumber);
    void serveRequest(double currentTime, const Request & request);
    double getServiceStartTime() const;
    double getServiceFinishTime() const;
    void print() const;

    friend std::ostream& operator<<(std::ostream & stream, const Server & server);
private:
    double serviceStartTime_;
    double serviceFinishTime_;
};

#endif // SERVER_H
