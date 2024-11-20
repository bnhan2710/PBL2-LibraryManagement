#include "PublisherService.h"

PublisherService* PublisherService::_publisherService = nullptr;

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

void PublisherService::addPublisher(const string& publisherName, const string& address, const string& contactInfo) {
    int publisherId = this->_publisherList.GetLength() + 1;
    Publisher publisher(publisherId, publisherName, address, contactInfo);
    this->_publisherList.InsertLast(publisher);
    this->_publisherRepository->addPublisher(publisher);
}

void PublisherService::updatePublisher(const int publisherId, const string& publisherName, const string& address, const string& contactInfo) {
    Publisher isExistedPublisher = this->_publisherRepository->getPublisherById( publisherId );
    if (isExistedPublisher.getPublisherId() == 0) {
        return;
    }
    isExistedPublisher.setPublisherName(publisherName);
    isExistedPublisher.setAddress(address);
    isExistedPublisher.setContactInfo(contactInfo);
    this->_publisherRepository->updatePublisher(isExistedPublisher);
}

void PublisherService::deletePublisher(const int publisherId) {
    Publisher isExistedPublisher = this->_publisherRepository->getPublisherById(publisherId);
    if (isExistedPublisher.getPublisherId() == 0) {
        return;
    }
    isExistedPublisher.setPublisherName("0");
    isExistedPublisher.setAddress("0");
    isExistedPublisher.setContactInfo("0");
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

