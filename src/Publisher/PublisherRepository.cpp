#include "PublisherRepository.h"

PublisherRepository* PublisherRepository::_publisherRepository = nullptr;
const char* PublisherRepository::_publisherFileName = "../../data/Publisher.txt";
const char* PublisherRepository::_publisherTempFileName = "../../data/TempPublisher.txt";

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
        cerr << "Không thể mở file để ghi." << endl;
        return;
    }

    outFile << publisher.getPublisherId() << " "
            << publisher.getPublisherName() << " "
            << publisher.getAddress() << " "
            << publisher.getContactInfo() << " " 
            << endl;

    outFile.close();
    cout << "Thêm nhà xuất bản thành công!" << endl;
}

void PublisherRepository::updatePublisher(Publisher publisher) {
    ifstream inFile(_publisherFileName);
    ofstream tempFile(_publisherTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << endl;
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
        cout << "Cập nhật nhà xuất bản thành công!" << endl;
    } else {
        remove(_publisherTempFileName);
        cout << "Nhà xuất bản không tồn tại!" << endl;
    }
}

void PublisherRepository::deletePublisher(int publisherId) {
    ifstream inFile(_publisherFileName);
    ofstream tempFile(_publisherTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << endl;
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
        cout << "Xóa nhà xuất bản thành công!" << endl;
    } else {
        remove(_publisherTempFileName);
        cout << "Nhà xuất bản không tồn tại!" << endl;
    }
}

Publisher PublisherRepository::getPublisherById(int publisherId) {
    ifstream inFile(_publisherFileName);
    if (!inFile.is_open()) {
        cerr << "Không thể mở file để đọc." << endl;
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
    cout << "Nhà xuất bản không tồn tại!" << endl;
    return Publisher();
}