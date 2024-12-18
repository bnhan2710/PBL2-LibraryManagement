#include "BookRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

BookRepository* BookRepository::_bookRepository = nullptr;
AuthorRepository* BookRepository::_authorRepository = nullptr;
CategoryRepository* BookRepository::_categoryRepository = nullptr;
PublisherRepository* BookRepository::_publisherRepository = nullptr;
const char* BookRepository::_bookFileName = "database/Book.txt";
const char* BookRepository::_bookTempFileName = "database/TempBook.txt";

BookRepository::BookRepository() {}

BookRepository* BookRepository::initBookRepository() {
    if (_bookRepository == nullptr) {
        _bookRepository = new BookRepository();
    }
    if (_authorRepository == nullptr) {
        _authorRepository = AuthorRepository::initAuthorRepository();
    }
    if (_categoryRepository == nullptr) {
        _categoryRepository = CategoryRepository::initCategoryRepository();
    }
    if (_publisherRepository == nullptr) {
        _publisherRepository = PublisherRepository::initPublisherRepository();
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
            << book.getAuthor().getAuthorName() << "|"
            << book.getCategory().getCategoryName() << "|"
            << book.getPublisher().getPublisherName() << "|"
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
                     << book.getAuthor().getAuthorName() << "|"
                     << book.getCategory().getCategoryName() << "|"
                     << book.getPublisher().getPublisherName() << "|"
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
    List<Author> authorList = _authorRepository->getAllAuthors();
    List<Category> categoryList = _categoryRepository->getAllCategories();
    List<Publisher> publisherList = _publisherRepository->getAllPublishers();
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return Book();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, code, title, author, category, publisher, quantityStr;
        int authorId, categoryId, publisherId;
        authorId = categoryId = publisherId = -1;
        getline(ss, idStr, '|');
        getline(ss, code, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, publisher, '|');
        getline(ss, quantityStr, '|');
        for( int i = 0; i < authorList.GetLength(); i++) {
            if (authorList[i].getAuthorName() == author) {
                authorId = i;
                break;
            }
        }

        for( int i = 0; i < categoryList.GetLength(); i++) {
            if (categoryList[i].getCategoryName() == category) {
                categoryId = i;
                break;
            }
        }

        for( int i = 0; i < publisherList.GetLength(); i++) {
            if (publisherList[i].getPublisherName() == publisher) {
                publisherId = i;
                break;
            }
        }

        if ( authorId == -1 || categoryId == -1 || publisherId == -1 ) {
            continue;
        }

        int id = atoi(idStr.c_str());
        if (id == bookId) {
            inFile.close();
            return Book(id, code, title, authorList[authorId], categoryList[categoryId], publisherList[publisherId], atoi(quantityStr.c_str()));
        }
    }
    inFile.close();
    cout << "Book not found" << endl;
    return Book();
}

List<Book> BookRepository::getAllBooks() {
    ifstream inFile(_bookFileName);
    ofstream tempFile(_bookTempFileName, ios::out);
    List<Book> bookList;
    List<Author> authorList = _authorRepository->getAllAuthors();
    List<Category> categoryList = _categoryRepository->getAllCategories();
    List<Publisher> publisherList = _publisherRepository->getAllPublishers();
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return bookList;
    }

    int authorId, categoryId, publisherId;
    authorId = categoryId = publisherId = -1;
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

        for( int i = 0; i < categoryList.GetLength(); i++) {
            if (categoryList[i].getCategoryName() == category) {
                categoryId = i;
                break;
            }
        }

        for( int i = 0; i < publisherList.GetLength(); i++) {
            if (publisherList[i].getPublisherName() == publisher) {
                publisherId = i;
                break;
            }
        }

        for( int i = 0; i < authorList.GetLength(); i++) {
            if (authorList[i].getAuthorName() == author) {
                authorId = i;
                break;
            }
        }

        if ( authorId == -1 ) {
            author = "0";
        }

        if ( categoryId == -1 ) {
            category = "0";
        }

        if ( publisherId == -1 ) {
            publisher = "0";
        }

        tempFile << idStr << "|"
                << code << "|"
                << title << "|"
                << author << "|"
                << category << "|"
                << publisher << "|"
                << atoi(quantityStr.c_str()) << endl;

        authorId = categoryId = publisherId = -1;
    }

    inFile.close();
    tempFile.close();
    remove(_bookFileName);
    rename(_bookTempFileName, _bookFileName);

    ifstream inFile2(_bookFileName);
    if (!inFile2.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return bookList;
    }
    while (getline(inFile2, line)) {
        stringstream ss(line);
        string idStr, code, title, author, category, publisher, quantityStr;

        getline(ss, idStr, '|');
        getline(ss, code, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, publisher, '|');
        getline(ss, quantityStr, '|');

        for( int i = 0; i < categoryList.GetLength(); i++) {
            if (categoryList[i].getCategoryName() == category) {
                categoryId = i;
                break;
            }
        }

        for( int i = 0; i < publisherList.GetLength(); i++) {
            if (publisherList[i].getPublisherName() == publisher) {
                publisherId = i;
                break;
            }
        }

        for( int i = 0; i < authorList.GetLength(); i++) {
            if (authorList[i].getAuthorName() == author) {
                authorId = i;
                break;
            }
        }

        if ( authorId == -1 || categoryId == -1 || publisherId == -1 ) {
            continue;
        }
        
        int id = atoi(idStr.c_str());
        bookList.InsertLast(Book(id, code, title, authorList[authorId], categoryList[categoryId], publisherList[publisherId], atoi(quantityStr.c_str())));
        authorId = categoryId = publisherId = -1;
    }
    inFile.close();
    return bookList;
}
