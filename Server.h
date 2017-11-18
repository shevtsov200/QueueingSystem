#ifndef SERVER_H
#define SERVER_H

#include "Request.h"
#include "Component.h"

#include <iosfwd>
#include <string>

class Server : public Component
{
public:
    Server();
    Server(int indexNumber, double lambda);
    void serveRequest(double currentTime, const Request & request);
    double getServiceStartTime() const;
    double getServiceFinishTime() const;
    double getAllServiceTime() const;
    void print() const;

    std::string getServerName() const;
    friend std::ostream& operator<<(std::ostream & stream, const Server & server);
private:
    double serviceStartTime_;
    double serviceFinishTime_;

    double allServiceTime_;
    double lambda_;
};

#endif // SERVER_H
