#ifndef CLIENT_H
#define CLIENT_H

#include "Request.h"

class Client
{
public:
    Client();
    Request generateRequest(double currentTime);
};

#endif // CLIENT_H
