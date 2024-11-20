#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H
#include "Book.h"
#include <iostream>
#include <fstream>
#include "../../utils/List.h"
using namespace std;
class BookRepository {
private:
    static BookRepository* _bookRepository;
    static const char* _bookFileName;
    static const char* _bookTempFileName;
    BookRepository();
public:
    static BookRepository *initBookRepository();
    ~BookRepository();
    void addBook(Book book);
    void updateBook(Book book);
    void deleteBook(int bookId);
    Book getBookById(int bookId);
    List<Book> getAllBooks();
    
};
#endif
