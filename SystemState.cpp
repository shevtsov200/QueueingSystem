#include "SystemState.h"

SystemState::SystemState(std::vector<Client> clients, Buffer buffer, std::vector<Server> servers,
                         std::vector<Request> rejected)
{
    clients_ = clients;
    buffer_ = buffer;
    servers_ = servers;
    rejected_ = rejected;
    generatingClientIndex_ = -1;
}
