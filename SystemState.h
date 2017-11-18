#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include "Request.h"
#include "Client.h"
#include "Buffer.h"
#include "Server.h"

struct SystemState
{
    std::vector<Client> clients_;
    Buffer buffer_;
    std::vector<Server> servers_;
    std::vector<Request> rejected_;

    SystemState(std::vector<Client> clients, Buffer buffer, std::vector<Server> servers,
                std::vector<Request> rejected);
};

#endif // SYSTEMSTATE_H
