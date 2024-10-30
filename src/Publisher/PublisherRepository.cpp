#include "PublisherRepository.h"

PublisherRepository* PublisherRepository::_publisherRepository = nullptr;
const char* PublisherRepository::_publisherFileName = "database/Publisher.txt";
const char* PublisherRepository::_publisherTempFileName = "database/TempPublisher.txt";

PublisherRepository::PublisherRepository() {
}

PublisherRepository* PublisherRepository::initPublisherRepository() {
    if (_publisherRepository == nullptr) {
        _publisherRepository = new PublisherRepository();
    }
    return _publisherRepository;
}

PublisherRepository::~PublisherRepository() {
}

void PublisherRepository::addPublisher(Publisher publisher) {
    ofstream outFile;
    outFile.open(_publisherFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    outFile << publisher.getPublisherId() << " "
            << publisher.getPublisherName() << " "
            << publisher.getAddress() << " "
            << publisher.getContactInfo() << " " 
            << endl;

    outFile.close();
    cout << "Add publisher successful" << endl;
}

void PublisherRepository::updatePublisher(Publisher publisher) {
    ifstream inFile(_publisherFileName);
    ofstream tempFile(_publisherTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    bool found = false;
    int PublisherId;
    string PublisherName, Address, ContactInfo;
    while( inFile >> PublisherId >> PublisherName >> Address >> ContactInfo ) {
        if ( PublisherId == publisher.getPublisherId() ) {
            tempFile << publisher.getPublisherId() << " "
                     << publisher.getPublisherName() << " "
                     << publisher.getAddress() << " "
                     << publisher.getContactInfo() << " " 
                     << endl;
            found = true;
        } else {
            tempFile << PublisherId << " "
                     << PublisherName << " "
                     << Address << " "
                     << ContactInfo << " " 
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_publisherFileName);
        rename(_publisherTempFileName, _publisherFileName);
        cout << "Updated publisher successful" << endl;
    } else {
        remove(_publisherTempFileName);
        cout << "Publisher not found" << endl;
    }
}

void PublisherRepository::deletePublisher(int publisherId) {
    ifstream inFile(_publisherFileName);
    ofstream tempFile(_publisherTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }
    bool found = false;
    int PublisherId;
    string PublisherName, Address, ContactInfo;
    while (inFile >> PublisherId >> PublisherName >> Address >> ContactInfo) {
        if (PublisherId == publisherId) {
            found = true;
        } else {
            tempFile << PublisherId << " "
                     << PublisherName << " "
                     << Address << " "
                     << ContactInfo << " " 
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_publisherFileName);
        rename(_publisherTempFileName, _publisherFileName);
        cout << "Deleted publisher successful" << endl;
    } else {
        remove(_publisherTempFileName);
        cout << "Publisher not found" << endl;
    }
}

Publisher PublisherRepository::getPublisherById(int publisherId) {
    ifstream inFile(_publisherFileName);
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return Publisher();
    }
    int PublisherId;
    string PublisherName, Address, ContactInfo;
    while (inFile >> PublisherId >> PublisherName >> Address >> ContactInfo) {
        if (PublisherId == publisherId) {
            inFile.close();
            return Publisher(PublisherId, PublisherName, Address, ContactInfo);
        }
    }
    inFile.close();
    cout << "PublisherId not found" << endl;
    return Publisher();
}

List<Publisher> PublisherRepository::getAllPublishers() {
    ifstream inFile(_publisherFileName);
    List<Publisher> publishers;
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return publishers;
    }
    int PublisherId;
    string PublisherName, Address, ContactInfo;
    while (inFile >> PublisherId >> PublisherName >> Address >> ContactInfo) {
        publishers.InsertLast(Publisher(PublisherId, PublisherName, Address, ContactInfo));
    }
    inFile.close();
    return publishers;
}