#ifndef CLIENT_H
#define CLIENT_H

#include "Request.h"
#include "Component.h"
#include <iosfwd>

class Client : public Component
{
public:
    Client();
    Client(int indexNumber);
    void generateRequest(double currentTime);
    double getRequestCreationTime() const;

    friend std::ostream &operator<<(std::ostream &stream, const Client &client);
private:
    int testInc_;
};

#endif // CLIENT_H
