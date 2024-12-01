#include "PublisherRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

PublisherRepository* PublisherRepository::_publisherRepository = nullptr;
const char* PublisherRepository::_publisherFileName = "database/Publisher.txt";
const char* PublisherRepository::_publisherTempFileName = "database/TempPublisher.txt";

PublisherRepository::PublisherRepository() {}

PublisherRepository* PublisherRepository::initPublisherRepository() {
    if (_publisherRepository == nullptr) {
        _publisherRepository = new PublisherRepository();
    }
    return _publisherRepository;
}

PublisherRepository::~PublisherRepository() {}

void PublisherRepository::addPublisher(const Publisher& publisher) {
    ofstream outFile(_publisherFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to write" << endl;
        return;
    }

    outFile << publisher.getPublisherId() << "|"
            << publisher.getPublisherName() << "|"
            << publisher.getAddress() << "|"
            << publisher.getContactInfo() << endl;

    outFile.close();
    cout << "Add publisher successful" << endl;
}

void PublisherRepository::updatePublisher(const Publisher& publisher) {
    ifstream inFile(_publisherFileName);
    ofstream tempFile(_publisherTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, address, contactInfo;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, address, '|');
        getline(ss, contactInfo, '|');

        int id = atoi(idStr.c_str());

        if (id == publisher.getPublisherId()) {
            tempFile << publisher.getPublisherId() << "|"
                     << publisher.getPublisherName() << "|"
                     << publisher.getAddress() << "|"
                     << publisher.getContactInfo() << endl;
            found = true;
        } else {
            tempFile << idStr << "|" << name << "|" << address << "|" << contactInfo << endl;
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_publisherFileName);
        rename(_publisherTempFileName, _publisherFileName);
        cout << "Updated publisher successfully" << endl;
    } else {
        remove(_publisherTempFileName);
        cout << "Publisher not found" << endl;
    }
}

void PublisherRepository::deletePublisher(int publisherId) {
    ifstream inFile(_publisherFileName);
    ofstream tempFile(_publisherTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, address, contactInfo;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, address, '|');
        getline(ss, contactInfo, '|');

        int id = atoi(idStr.c_str());

        if (id == publisherId) {
            found = true;
        } else {
            tempFile << idStr << "|" << name << "|" << address << "|" << contactInfo << endl;
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_publisherFileName);
        rename(_publisherTempFileName, _publisherFileName);
        cout << "Deleted publisher successfully" << endl;
    } else {
        remove(_publisherTempFileName);
        cout << "Publisher not found" << endl;
    }
}

Publisher PublisherRepository::getPublisherById(int publisherId) {
    ifstream inFile(_publisherFileName);
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return Publisher();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, address, contactInfo;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, address, '|');
        getline(ss, contactInfo, '|');

        int id = atoi(idStr.c_str());

        if (id == publisherId) {
            inFile.close();
            return Publisher(id, name, address, contactInfo);
        }
    }

    inFile.close();
    cout << "Publisher not found" << endl;
    return Publisher();
}

List<Publisher> PublisherRepository::getAllPublishers() {
    ifstream inFile(_publisherFileName);
    List<Publisher> publishers;
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return publishers;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, address, contactInfo;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, address, '|');
        getline(ss, contactInfo, '|');

        int id = atoi(idStr.c_str());

        publishers.InsertLast(Publisher(id, name, address, contactInfo));
    }

    inFile.close();
    return publishers;
}
