#include "BookRepository.h"

BookRepository* BookRepository::_bookRepository = nullptr;
const char* BookRepository::_bookFileName = "database/Book.txt";
const char* BookRepository::_bookTempFileName = "database/TempBook.txt";

BookRepository::BookRepository() {
}

BookRepository* BookRepository::initBookRepository() {
    if (_bookRepository == nullptr) {
        _bookRepository = new BookRepository();
    }
    return _bookRepository;
}

BookRepository::~BookRepository() {
}

void BookRepository::addBook(Book book) {
    ofstream outFile;
    outFile.open(_bookFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    outFile << book.getBookId() << " "
            << book.getCode() << " "
            << book.getTitle() << " "
            << book.getAuthor() << " "
            << book.getCategory() << " "
            << book.getPublisher() << " "
            << book.getQuantity() << " "
            << endl;

    outFile.close();
    cout << "Add book successful" << endl;
}

void BookRepository::updateBook(Book book) {
    ifstream inFile(_bookFileName);
    ofstream tempFile(_bookTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    bool found = false;
    int BookId;
    string Title, Author, Category, Publisher, Code;
    int Quantity;
    while( inFile >> BookId >> Code >> Title >> Author >> Category >> Publisher >> Quantity ) {
        if ( BookId == book.getBookId() ) {
            tempFile << book.getBookId() << " "
                     << book.getCode() << " "
                     << book.getTitle() << " "
                     << book.getAuthor() << " "
                     << book.getCategory() << " "
                     << book.getPublisher() << " "
                     << book.getQuantity() << " "
                     << endl;
            found = true;
        } else {
            tempFile << BookId << " "
                     << Title << " "
                     << Author << " "
                     << Category << " "
                     << Publisher << " "
                     << Quantity << " "
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_bookFileName);
        rename(_bookTempFileName, _bookFileName);
        cout << "Updated book successful" << endl;
    } else {
        remove(_bookTempFileName);
        cout << "Book not found" << endl;
    }
}

void BookRepository::deleteBook(int bookId) {
    ifstream inFile(_bookFileName);
    ofstream tempFile(_bookTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }
    bool found = false;
    int BookId;
    string Title, Author, Category, Publisher, Code;
    int Quantity;
    while (inFile >> BookId >> Code >> Title >> Author >> Category >> Publisher >> Quantity) {
        if (BookId == bookId) {
            found = true;
        } else {
            tempFile << BookId << " "
                     << Code << " "
                     << Title << " "
                     << Author << " "
                     << Category << " "
                     << Publisher << " "
                     << Quantity << " "
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_bookFileName);
        rename(_bookTempFileName, _bookFileName);
        cout << "Deleted book successful" << endl;
    } else {
        remove(_bookTempFileName);
        cout << "Book not found" << endl;
    }
}

Book BookRepository::getBookById(int bookId) {
    ifstream inFile(_bookFileName);
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return Book();
    }
    int BookId;
    string Title, Author, Category, Publisher, Code;
    int Quantity;
    while (inFile >> BookId >> Code >> Title >> Author >> Category >> Publisher >> Quantity) {
        if (BookId == bookId) {
            inFile.close();
            return Book(BookId, Code, Title, Author, Category, Publisher, Quantity);
        }
    }
    inFile.close();
    return Book();
}

List<Book> BookRepository::getAllBooks() {
    ifstream inFile(_bookFileName);
    List<Book> bookList;
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return bookList;
    }
    int BookId;
    string Title, Author, Category, Publisher, Code;
    int Quantity;
    while (inFile >> BookId >> Code >> Title >> Author >> Category >> Publisher >> Quantity) {
        bookList.InsertLast(Book(BookId, Code, Title, Author, Category, Publisher, Quantity));
    }
    inFile.close();
    return bookList;
}

