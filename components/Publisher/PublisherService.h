#ifndef PUBLISHERSERVICE_H
#define PUBLISHERSERVICE_H
#include "Publisher.h"
#include "PublisherRepository.h"
#include "../../utils/List.h"
class PublisherService {
private:
    static PublisherService* _publisherService;
    PublisherRepository* _publisherRepository;
    List<Publisher> _publisherList;
    PublisherService();
public:
    ~PublisherService();
    static PublisherService* initPublisherService();
    void addPublisher(const string&, const string&, const string&);
    void updatePublisher(const int, const string&, const string&, const string&);
    void deletePublisher(const int);
    List<Publisher> getPublisher( int );
    List<Publisher> getPublisher();

};
#endif
