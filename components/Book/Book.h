#ifndef BOOK_H
#define BOOK_H
#include <string>
#include "../Category/Category.h"
#include "../Author/Author.h"
#include "../Publisher/Publisher.h"
using namespace std;
class Book {
private:
    int bookId;
    string title;
    Author author;
    int quantity;
    int num_of_pages;
    int publisherId;
    int categoryId;
    Category category;
    Publisher publisher;
public:
    Book();
    Book(int bookId, string title, Author author, int quantity, int num_of_pages, int publisherId, int categoryId);
    ~Book();

    void setBookId(int bookId);
    int getBookId();
    
    void setTitle(string title);
    string getTitle();
    
    void setAuthor(Author author);
    Author getAuthor();
    
    void setQuantity(int quantity);
    int getQuantity();
    
    void setNumOfPages(int num_of_pages);
    int getNumOfPages();
    
    void setPublisherId(int publisherId);
    int getPublishetId();
    
    void setCategoryId(int categoryId);
    int getCategoryId();

    void setCategory(Category category);
    Category getCategory();

    void setPublisher(Publisher publisher);
    Publisher getPublisher();
};
#endif
