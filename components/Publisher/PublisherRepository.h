#ifndef PUBLISHERREPOSITORY_H
#define PUBLISHERREPOSITORY_H
#include "Publisher.h"
#include <iostream>
#include <fstream>
#include "../../utils/List.h"
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
    void addPublisher(const Publisher& publisher);
    void updatePublisher(const Publisher& publisher);
    void deletePublisher(int publisherId);
    Publisher getPublisherById(int publisherId);
    List<Publisher> getAllPublishers();
    
};                  
#endif
