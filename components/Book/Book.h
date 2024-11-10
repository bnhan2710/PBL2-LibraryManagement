#ifndef BOOK_H
#define BOOK_H
#include <string>
#include "../Category/Category.h"
#include "../Author/Author.h"
#include "../Publisher/Publisher.h"
using namespace std;
#ifndef DATE
#define DATE
struct Date {
    int day;
    int month;
    int year;
};
#endif
class Book {
private:
    int bookId;
    string title;
    Author author;
    Publisher publisher;
    Category category;
    int quantity;
    Date publishedDate;
public:
    Book();
    Book( int bookId, string& title, Author& author, Publisher& publisher, Category& category, int& quantity, Date& publishedDate );
    void setBookId( int bookId );
    int getBookId();
    void setTitle( string title );
    string getTitle();
    void setAuthor( Author author );
    Author getAuthor();
    void setPublisher( Publisher publisher );
    Publisher getPublisher();
    void setCategory( Category category );
    Category getCategory();
    void setPublishedDate( Date publishedDate );
    Date getPublishedDate();
    void setQuantity( int quantity );
    int getQuantity();
};
#endif
