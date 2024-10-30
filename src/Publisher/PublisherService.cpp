#include "PublisherService.h"

PublisherService* PublisherService::_publisherService = nullptr;
string publisherName, address, contactInfo;
int publisherId;

PublisherService::PublisherService() {
    this->_publisherRepository = PublisherRepository::initPublisherRepository();
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
    cout << "Enter publisher ID: ";
    cin >> publisherId;
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
    this->_publisherRepository->addPublisher(publisher);
}

void PublisherService::updatePublisher() {
    Publisher isExistedPublisher = getPublisherById();
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
    this->_publisherRepository->deletePublisher(publisherId);
}

Publisher PublisherService::getPublisherById() {
    cout << "Enter publisher ID: ";
    cin >> publisherId;
    cin.ignore();
    return this->_publisherRepository->getPublisherById(publisherId);
}

