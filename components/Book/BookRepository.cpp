#include "BookRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

BookRepository* BookRepository::_bookRepository = nullptr;
const char* BookRepository::_bookFileName = "database/Book.txt";
const char* BookRepository::_bookTempFileName = "database/TempBook.txt";

BookRepository::BookRepository() {}

BookRepository* BookRepository::initBookRepository() {
    if (_bookRepository == nullptr) {
        _bookRepository = new BookRepository();
    }
    return _bookRepository;
}

BookRepository::~BookRepository() {}

void BookRepository::addBook(const Book& book) {
    ofstream outFile(_bookFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to write" << endl;
        return;
    }

    outFile << book.getBookId() << "|"
            << book.getCode() << "|"
            << book.getTitle() << "|"
            << book.getAuthor() << "|"
            << book.getCategory() << "|"
            << book.getPublisher() << "|"
            << book.getQuantity() << endl;

    outFile.close();
    cout << "Add book successful" << endl;
}

void BookRepository::updateBook(const Book& book) {
    ifstream inFile(_bookFileName);
    ofstream tempFile(_bookTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, code, title, author, category, publisher, quantityStr;

        getline(ss, idStr, '|');
        getline(ss, code, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, publisher, '|');
        getline(ss, quantityStr, '|');

        int id = atoi(idStr.c_str());

        if (id == book.getBookId()) {
            tempFile << book.getBookId() << "|"
                     << book.getCode() << "|"
                     << book.getTitle() << "|"
                     << book.getAuthor() << "|"
                     << book.getCategory() << "|"
                     << book.getPublisher() << "|"
                     << book.getQuantity() << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_bookFileName);
        rename(_bookTempFileName, _bookFileName);
        cout << "Updated book successfully" << endl;
    } else {
        remove(_bookTempFileName);
        cout << "Book not found" << endl;
    }
}

void BookRepository::deleteBook(int bookId) {
    ifstream inFile(_bookFileName);
    ofstream tempFile(_bookTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr;

        getline(ss, idStr, '|');

        int id = atoi(idStr.c_str());

        if (id == bookId) {
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_bookFileName);
        rename(_bookTempFileName, _bookFileName);
        cout << "Deleted book successfully" << endl;
    } else {
        remove(_bookTempFileName);
        cout << "Book not found" << endl;
    }
}

Book BookRepository::getBookById(int bookId) {
    ifstream inFile(_bookFileName);
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return Book();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, code, title, author, category, publisher, quantityStr;

        getline(ss, idStr, '|');
        getline(ss, code, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, publisher, '|');
        getline(ss, quantityStr, '|');

        int id = atoi(idStr.c_str());
        if (id == bookId) {
            inFile.close();
            return Book(id, code, title, author, category, publisher, atoi(quantityStr.c_str()));
        }
    }

    inFile.close();
    cout << "Book not found" << endl;
    return Book();
}

List<Book> BookRepository::getAllBooks() {
    ifstream inFile(_bookFileName);
    List<Book> bookList;
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return bookList;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, code, title, author, category, publisher, quantityStr;

        getline(ss, idStr, '|');
        getline(ss, code, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, publisher, '|');
        getline(ss, quantityStr, '|');

        int id = atoi(idStr.c_str());
        bookList.InsertLast(Book(id, code, title, author, category, publisher, atoi(quantityStr.c_str())));
    }

    inFile.close();
    return bookList;
}
