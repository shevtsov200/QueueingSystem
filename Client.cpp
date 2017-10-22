#include <cstdlib>
#include "Client.h"

#include "Request.h"

Client::Client()
{

}

Request Client::generateRequest(double currentTime)
{
    const double a = 0;
    const double b = 5;
    double creationTime = currentTime + ((double)std::rand() / (double)RAND_MAX) * (b - a) + a;
    Request request = Request(creationTime);
    return request;
}
