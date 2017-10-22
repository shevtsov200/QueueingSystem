#ifndef REQUEST_H
#define REQUEST_H

class Request
{
public:
    Request();
    Request(double creationTime);

    double getCreationTime() const;
    double getEndTime() const;

    void setEndTime(double endTime);
private:
    double creationTime_;
    double endTime_;
};

#endif // REQUEST_H
