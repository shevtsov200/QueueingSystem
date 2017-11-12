#ifndef STATISTICS_H
#define STATISTICS_H

#include "Client.h"
#include "Request.h"
#include "Server.h"

#include <vector>

class Statistics
{
public:
    Statistics();
    Statistics(const std::vector<Client> &clients, const std::vector<Request> &rejectedRequests,
               const std::vector<Request> &servicedRequests, std::vector<Server> &servers, double executionTime);
    void calculateStatistics();
    void printClientTable() const;
    void printServerTable() const;

    const std::vector<int> & getClientsIndexes() const;
    const std::vector<int> & getClientRequestCounts() const;
    const std::vector<double> & getRejectProbabilities() const;
    const std::vector<double> & getSystemStayMeans() const;
    const std::vector<double> & getBufferStayMeans() const;
    const std::vector<double> & getServiceStayMeans() const;
    const std::vector<double> & getBufferVariances() const;
    const std::vector<double> & getServiceVariances() const;
    const std::vector<double> & getUtilizationFactors() const;
    int getAllRequestCount(int index) const;
private:
    std::vector<Client> clients_;
    std::vector<Server> servers_;
    std::vector<Request> rejectedRequests_, servicedRequests_;

    std::vector<Request> requests_;
    std::vector<int> clientsNumbers_, allRequestsCounts_,
    rejectedRequestsCounts_;
    std::vector<double> rejectProbabilities_,
    systemStayMeans_, bufferStayMeans_,
    serviceStayMeans_, bufferVariances_,
    serviceVariances_, utilizationFactors_;
    double executionTime_;


    double calculateRejectProbability(double rejectedRequestsCount, double allRequestsCount) const;
    double calculateVariance(const std::vector<double> & values) const;
    double calculateMean(const std::vector<double> & values) const;
    void filterClientRequests(int clientNumber, const std::vector<Request> &source, std::vector<Request> &destination) const;
    void calculateBufferStayTimes(const std::vector<Request> &requests, std::vector<double> &bufferStayTimes);
    void calculateServiceStayTimes(const std::vector<Request> &requests, std::vector<double> &serviceStayTimes);
};

#endif // STATISTICS_H
