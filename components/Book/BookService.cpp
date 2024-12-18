#include "BookService.h"

BookService* BookService::_bookService = nullptr;

BookService::BookService() {
    this->_bookRepository = BookRepository::initBookRepository();
    this->_bookList = this->_bookRepository->getAllBooks();
}

BookService* BookService::initBookService() {
    if ( _bookService == nullptr ) {
        _bookService = new BookService();
    }
    return _bookService;
}

BookService::~BookService() {
}

void BookService::addBook(const string& code, const string& title, Author& author, Category& category, Publisher& publisher, const int quantity) {
    int bookId = this->_bookList.GetLength() + 1;
    Book book(bookId, code, title, author, category, publisher, quantity);
    this->_bookList.InsertLast(book);
    this->_bookRepository->addBook(book);
}

void BookService::updateBook(const int bookId, const string& code, const string& title, Author& author, Category& category, Publisher& publisher, const int quantity) {
    Book isExistedBook = this->_bookRepository->getBookById( bookId );
    if (isExistedBook.getBookId() == 0) {
        return;
    }
    isExistedBook.setCode(code);
    isExistedBook.setTitle(title);
    isExistedBook.setAuthor(author);
    isExistedBook.setCategory(category);
    isExistedBook.setPublisher(publisher);
    isExistedBook.setQuantity(quantity);
    this->_bookRepository->updateBook(isExistedBook);
}

void BookService::deleteBook(const int bookId) {
    Book isExistedBook = this->_bookRepository->getBookById(bookId);
    if (isExistedBook.getBookId() == 0) {
        return;
    }
    isExistedBook.setCode("0");
    isExistedBook.setTitle("0");
    /* isExistedBook.setAuthor("0"); */
    /* isExistedBook.setCategory("0"); */
    /* isExistedBook.setPublisher("0"); */
    isExistedBook.setQuantity(0);
    this->_bookRepository->updateBook(isExistedBook);
}

List<Book> BookService::getBook( int bookId ) {
    List<Book> books;
    Book book = this->_bookRepository->getBookById(bookId);
    books.InsertLast(book);
    return books;
}

List<Book> BookService::getBook() {
    return this->_bookRepository->getAllBooks();
}


