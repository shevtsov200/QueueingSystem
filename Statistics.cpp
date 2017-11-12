#include "Statistics.h"
#include "Request.h"
#include "Client.h"
#include "Server.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include <iomanip>

Statistics::Statistics()
{

}

Statistics::Statistics(const std::vector<Client> &clients, const std::vector<Request> &rejectedRequests,
                       const std::vector<Request> &servicedRequests, std::vector<Server> &servers, double executionTime)
{
    clients_ = clients;
    servers_ = servers;
    rejectedRequests_ = rejectedRequests;
    servicedRequests_ = servicedRequests;
    executionTime_ = executionTime;

    requests_.insert(requests_.begin(),rejectedRequests_.begin(),rejectedRequests_.end());
    requests_.insert(requests_.begin(),servicedRequests_.begin(),servicedRequests_.end());
}

void Statistics::calculateStatistics()
{
    for(std::size_t i = 0; i < clients_.size(); ++i)
    {
        std::vector<Request> clientRequests;
        filterClientRequests(i,requests_,clientRequests);

        std::vector<Request> clientRejectedRequests;
        filterClientRequests(i,rejectedRequests_,clientRejectedRequests);

        int clientRequestsCount = clientRequests.size();
        allRequestsCounts_.push_back(clientRequestsCount);

        int rejectedRequestsCount = clientRejectedRequests.size();
        rejectedRequestsCounts_.push_back(rejectedRequestsCount);

        double rejectProbability = calculateRejectProbability(double(rejectedRequestsCount), double(clientRequestsCount));
        rejectProbabilities_.push_back(rejectProbability);

        std::vector<double> bufferStayTimes;
        calculateBufferStayTimes(clientRequests, bufferStayTimes);

        double bufferMean = calculateMean(bufferStayTimes);
        bufferStayMeans_.push_back(bufferMean);

        double bufferVariance = calculateVariance(bufferStayTimes);
        bufferVariances_.push_back(bufferVariance);

        std::vector<double> serviceStayTimes;
        calculateServiceStayTimes(clientRequests, serviceStayTimes);

        double serviceMean = calculateMean(serviceStayTimes);
        serviceStayMeans_.push_back(serviceMean);

        double serviceVariance = calculateVariance(serviceStayTimes);
        serviceVariances_.push_back(serviceVariance);

        double systemStayMean = bufferMean + serviceMean;
        systemStayMeans_.push_back(systemStayMean);
    }
}

double Statistics::calculateRejectProbability(double rejectedRequestsCount, double allRequestsCount) const
{
    double rejectProbability = rejectedRequestsCount / allRequestsCount;
    return rejectProbability;
}

double Statistics::calculateVariance(const std::vector<double> &values) const
{
    double mean = calculateMean(values);
    double squareSum = std::inner_product(values.cbegin(), values.cend(),
                                          values.cbegin(),0.0);
    double variance = squareSum/values.size() - mean*mean;
    return variance;
}

double Statistics::calculateMean(const std::vector<double> &values) const
{
    double sum = std::accumulate(values.cbegin(),values.cend(),0.0);
    double mean = sum / values.size();
    return mean;
}

void Statistics::filterClientRequests(int clientNumber, const std::vector<Request> &source, std::vector<Request> &destination) const
{
    std::copy_if(source.cbegin(), source.cend(), std::back_inserter(destination),
                 [=](const Request & request)
    {
        return (request.getClientNumber() == clientNumber);
    });
}

void Statistics::calculateBufferStayTimes(const std::vector<Request> &requests, std::vector<double> &bufferStayTimes)
{
    std::transform(requests.cbegin(), requests.cend(), std::back_inserter(bufferStayTimes),
                   [](const Request & request)
    {
        if(request.getServiceStartTime() != 0)
        {
            return (request.getServiceStartTime() - request.getCreationTime());
        }
        else
        {
            return (request.getEndTime() - request.getCreationTime());
        }

    });
}

void Statistics::calculateServiceStayTimes(const std::vector<Request> &requests, std::vector<double> &serviceStayTimes)
{
    std::transform(requests.cbegin(), requests.cend(), std::back_inserter(serviceStayTimes),
                   [](const Request & request)
    {
        if (request.getServiceStartTime() != 0)
        {
            return (request.getEndTime() - request.getServiceStartTime());
        }
        else
        {
            return 0.0;
        }
    });
}

void Statistics::printClientTable() const
{
    const int spacingNumber = 13;
        std::cout << '|' << std::setw(spacingNumber) << "client"
                  << '|' << std::setw(spacingNumber) << "requestNumber"
                  << '|' << std::setw(spacingNumber) << "p_reject"
                  << '|' << std::setw(spacingNumber) << "T_sys"
                  << '|' << std::setw(spacingNumber) << "T_buf"
                  << '|' << std::setw(spacingNumber) << "T_serv"
                  << '|' << std::setw(spacingNumber) << "V_buf"
                  << '|' << std::setw(spacingNumber) << "V_serv"
                  << '|' << std::endl;
        for(std::size_t i = 0; i < clients_.size(); ++i)
        {
            std::cout << '|' << std::setw(spacingNumber) << clients_[i].getIndex()
                      << '|' << std::setw(spacingNumber) << allRequestsCounts_[i]
                      << '|' << std::setw(spacingNumber) << rejectProbabilities_[i]
                      << '|' << std::setw(spacingNumber) << systemStayMeans_[i]
                      << '|' << std::setw(spacingNumber) << bufferStayMeans_[i]
                      << '|' << std::setw(spacingNumber) << serviceStayMeans_[i]
                      << '|' << std::setw(spacingNumber) << bufferVariances_[i]
                      << '|' << std::setw(spacingNumber) << serviceVariances_[i]
                      << '|' << std::endl;
        }
}

void Statistics::printServerTable() const
{
    const int spacingNumber = 18;
    std::cout << '|' << std::setw(spacingNumber) << "server"
              << '|' << std::setw(spacingNumber) << "utilization factor"
              << '|' << std::endl;
    for(std::vector<Server>::const_iterator it = servers_.cbegin(); it != servers_.cend(); ++it)
    {
        double utilizationFactor = it->getAllServiceTime()/executionTime_;
        std::cout << '|' << std::setw(spacingNumber) << it->getIndex()
                  << '|' << std::setw(spacingNumber) << utilizationFactor
                  << '|' << std::endl;
    }
}

const std::vector<int> &Statistics::getClientsIndexes() const
{
    return clientsNumbers_;
}

const std::vector<int> &Statistics::getClientRequestCounts() const
{
return allRequestsCounts_;
}

const std::vector<double> &Statistics::getRejectProbabilities() const
{
    return rejectProbabilities_;
}

const std::vector<double> &Statistics::getSystemStayMeans() const
{
    return systemStayMeans_;
}

const std::vector<double> &Statistics::getBufferStayMeans() const
{
    return bufferStayMeans_;
}

const std::vector<double> &Statistics::getServiceStayMeans() const
{
    return serviceStayMeans_;
}

const std::vector<double> &Statistics::getBufferVariances() const
{
    return bufferVariances_;
}

const std::vector<double> &Statistics::getServiceVariances() const
{
    return serviceVariances_;
}
