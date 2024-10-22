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
    Publisher(int publisherId, string publisherName, string address, string contactInfo);
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