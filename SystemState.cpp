#include "SystemState.h"

SystemState::SystemState(std::vector<Client> clients, Buffer buffer, std::vector<Server> servers,
                         std::vector<Request> rejected, std::vector<Request> serviced)
{
    clients_ = clients;
    buffer_ = buffer;
    servers_ = servers;
    rejected_ = rejected;
    serviced_ = serviced;
    generatingClientIndex_ = -1;
}
