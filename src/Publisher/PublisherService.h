#ifndef PUBLISHERSERVICE_H
#define PUBLISHERSERVICE_H
#include "Publisher.h"
#include "PublisherRepository.h"
class PublisherService {
private:
    static PublisherService* _publisherService;
    PublisherRepository* _publisherRepository;
    PublisherService();
public:
    ~PublisherService();
    static PublisherService* initPublisherService();
    void addPublisher();
    void updatePublisher();
    void deletePublisher();
    Publisher getPublisherById();
};
#endif