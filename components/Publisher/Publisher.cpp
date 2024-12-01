#include "Publisher.h"

Publisher::Publisher() {
    this->publisherId = 0;
    this->publisherName = "";
    this->address = "";
    this->contactInfo = "";
}

Publisher::Publisher(const int publisherId, const string& publisherName, const string& address, const string& contactInfo) {
    this->publisherId = publisherId;
    this->publisherName = publisherName;
    this->address = address;
    this->contactInfo = contactInfo;
}

void Publisher::setPublisherId(int publisherId) {
    this->publisherId = publisherId;
}

int Publisher::getPublisherId() const {
    return this->publisherId;
}

void Publisher::setPublisherName(string publisherName) {
    this->publisherName = publisherName;
}

string Publisher::getPublisherName() const {
    return this->publisherName;
}

void Publisher::setAddress(string address) {
    this->address = address;
}

string Publisher::getAddress() const {
    return this->address;
}

void Publisher::setContactInfo(string contactInfo) {
    this->contactInfo = contactInfo;
}

string Publisher::getContactInfo() const {
    return this->contactInfo;
}
