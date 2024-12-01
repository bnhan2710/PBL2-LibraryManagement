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
    /* Author author; */
    /* Category category; */
    /* Publisher publisher; */
    string author;
    string category;
    string publisher;
    int quantity;
    string code;
    int num_of_pages;
    int publisherId;
    int categoryId;
public:
    Book();
    /* Book(int bookId, string title, Author author, int quantity, int num_of_pages, int publisherId, int categoryId); */
    Book(int bookId, string code, string title, string author, string category, string publisher, int quantity );
    ~Book();

    void setBookId(int bookId);
    int getBookId() const;
    
    void setTitle(string title);
    string getTitle() const;
    
    void setAuthor(string author);
    string getAuthor() const;

    void setCategory(string category);
    string getCategory() const;

    void setPublisher(string publisher);
    string getPublisher() const;

    void setCode(string code);
    string getCode() const;
    /* void setAuthor(Author author); */
    /* Author getAuthor(); */
    
    /* void setCategory(Category category); */
    /* Category getCategory(); */

    /* void setPublisher(Publisher publisher); */
    /* Publisher getPublisher(); */

    void setQuantity(int quantity);
    int getQuantity() const;
    
    void setNumOfPages(int num_of_pages);
    int getNumOfPages() const;
    
    void setPublisherId(int publisherId);
    int getPublisherId() const;
    
    void setCategoryId(int categoryId);
    int getCategoryId() const;

};
#endif
