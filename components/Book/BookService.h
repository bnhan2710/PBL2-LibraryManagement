#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H
#include "Book.h"
#include "BookRepository.h"
#include "../../utils/List.h"
class BookService {
private:
    static BookService* _bookService;
    BookRepository* _bookRepository;
    List<Book> _bookList;
    BookService();
public:
    ~BookService();
    static BookService* initBookService();
    void addBook(const string&, const string&, Author&, Category&, Publisher&, const int);
    void updateBook(const int, const string&, const string&, Author&, Category&, Publisher&, const int);
    void deleteBook(const int);
    List<Book> getBook( int );
    List<Book> getBook();

};
#endif
