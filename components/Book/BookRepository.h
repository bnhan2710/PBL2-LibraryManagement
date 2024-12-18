#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H
#include "Book.h"
#include "../Author/AuthorRepository.h"
#include "../Category/CategoryRepository.h"
#include "../Publisher/PublisherRepository.h"
#include <iostream>
#include <fstream>
#include "../../utils/List.h"
using namespace std;
class BookRepository {
private:
    static BookRepository* _bookRepository;
    static AuthorRepository* _authorRepository;
    static CategoryRepository* _categoryRepository;
    static PublisherRepository* _publisherRepository;
    static const char* _bookFileName;
    static const char* _bookTempFileName;
    BookRepository();
public:
    static BookRepository *initBookRepository();
    ~BookRepository();
    void addBook(const Book& book);
    void updateBook(const Book& book);
    void deleteBook(int bookId);
    Book getBookById(int bookId);
    List<Book> getAllBooks();
    
};
#endif
