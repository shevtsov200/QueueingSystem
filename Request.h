#ifndef REQUEST_H
#define REQUEST_H

#include <iosfwd>

class Request
{
public:
    Request();
    Request(double creationTime, int clientNumber, int requestNumber);

    double getCreationTime() const;
    double getServiceStartTime() const;
    double getEndTime() const;
    int getRequestNumber() const;
    int getClientNumber() const;

    void setServiceStartTime(double serviceStartTime);
    void setEndTime(double endTime);

    friend std::ostream& operator<<(std::ostream & stream, const Request & request);
private:
    double creationTime_;
    double serviceStartTime_;
    double endTime_;

    int clientNumber_;
    int requestNumber_;
};

#endif // REQUEST_H
