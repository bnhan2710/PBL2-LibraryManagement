#include "PublisherService.h"

PublisherService* PublisherService::_publisherService = nullptr;

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

void PublisherService::addPublisher(Publisher publisher) {
    this->_publisherRepository->addPublisher(publisher);
}

void PublisherService::updatePublisher(Publisher publisher) {
    this->_publisherRepository->updatePublisher(publisher);
}

void PublisherService::deletePublisher(int publisherId) {
    this->_publisherRepository->deletePublisher(publisherId);
}

Publisher PublisherService::getPublisherById(int publisherId) {
    return this->_publisherRepository->getPublisherById(publisherId);
}

