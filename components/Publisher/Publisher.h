#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <string>
using namespace std;
class Publisher {
private:
    int publisherId;
    string publisherName;
    string address;
    string contactInfo;
public:
    Publisher();
    Publisher(const int publisherId, const string& publisherName, const string& address, const string& contactInfo);
    void setPublisherId(int publisherId);
    int getPublisherId() const;
    void setPublisherName(string publisherName);
    string getPublisherName() const;
    void setAddress(string address);
    string getAddress() const;
    void setContactInfo(string contactInfo);
    string getContactInfo() const;
};

#endif
