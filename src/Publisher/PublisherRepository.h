#ifndef PUBLISHERREPOSITORY_H
#define PUBLISHERREPOSITORY_H
#include "Publisher.h"
#include <iostream>
#include <fstream>
using namespace std;
class PublisherRepository {
private:
    static PublisherRepository* _publisherRepository;
    static const char* _publisherFileName;
    static const char* _publisherTempFileName;
    PublisherRepository();
public:
    static PublisherRepository *initPublisherRepository();
    ~PublisherRepository();
    void addPublisher(Publisher publisher);
    void updatePublisher(Publisher publisher);
    void deletePublisher(int publisherId);
    Publisher getPublisherById(int publisherId);
};                  
#endif