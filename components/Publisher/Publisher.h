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
    int getPublisherId();
    void setPublisherName(string publisherName);
    string getPublisherName();
    void setAddress(string address);
    string getAddress();
    void setContactInfo(string contactInfo);
    string getContactInfo();
};

#endif
