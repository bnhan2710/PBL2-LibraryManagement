#include "PublisherService.h"

PublisherService* PublisherService::_publisherService = nullptr;
string publisherName, address, contactInfo;
int publisherId;

PublisherService::PublisherService() {
    this->_publisherRepository = PublisherRepository::initPublisherRepository();
    this->_publisherList = this->_publisherRepository->getAllPublishers();
}

PublisherService* PublisherService::initPublisherService() {
    if ( _publisherService == nullptr ) {
        _publisherService = new PublisherService();
    }
    return _publisherService;
}

PublisherService::~PublisherService() {
}

void PublisherService::addPublisher() {
    publisherId = this->_publisherList.GetLength() + 1;
    cin.ignore();
    cout << "Enter publisher name: ";
    cin >> publisherName;
    cin.ignore();
    cout << "Enter address: ";
    cin >> address;
    cin.ignore();
    cout << "Enter contact info: ";
    cin >> contactInfo;
    cin.ignore();
    Publisher publisher(publisherId, publisherName, address, contactInfo);
    this->_publisherList.InsertLast(publisher);
    this->_publisherRepository->addPublisher(publisher);
}

void PublisherService::updatePublisher() {
    cout << "Enter publisher ID: ";
    cin >> publisherId;
    cin.ignore();
    Publisher isExistedPublisher = this->_publisherRepository->getPublisherById( publisherId );
    if (isExistedPublisher.getPublisherId() == 0) {
        return;
    }
    int publisherChoice;
    do {
        cout << "=====================================\n";
        cout << "1. Update publisherName" << endl;
        cout << "2. Update address" << endl;
        cout << "3. Update contactInfo" << endl;
        cout << "4. Exit" << endl;
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> publisherChoice;
        switch (publisherChoice) {
            case 1:
                cout << "Enter new publisherName: ";
                cin >> publisherName;
                cin.ignore();
                isExistedPublisher.setPublisherName(publisherName);
                break;
            case 2:
                cout << "Enter new address: ";
                cin >> address;
                cin.ignore();
                isExistedPublisher.setAddress(address);
                break;
            case 3:
                cout << "Enter new contactInfo: ";
                cin >> contactInfo;
                cin.ignore();
                isExistedPublisher.setContactInfo(contactInfo);
                break;
            case 4: 
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (publisherChoice != 4);
    this->_publisherRepository->updatePublisher(isExistedPublisher);
}

void PublisherService::deletePublisher() {
    cout << "Enter publisher ID: ";
    cin >> publisherId;
    cin.ignore();
    Publisher isExistedPublisher = this->_publisherRepository->getPublisherById(publisherId);
    if (isExistedPublisher.getPublisherId() == 0) {
        return;
    }
    isExistedPublisher.setPublisherName("999");
    isExistedPublisher.setAddress("999");
    isExistedPublisher.setContactInfo("999");
    this->_publisherRepository->updatePublisher(isExistedPublisher);
}

List<Publisher> PublisherService::getPublisher( int publisherId ) {
    List<Publisher> publishers;
    Publisher publisher = this->_publisherRepository->getPublisherById(publisherId);
    publishers.InsertLast(publisher);
    return publishers;
}

List<Publisher> PublisherService::getPublisher() {
    return this->_publisherRepository->getAllPublishers();
}

