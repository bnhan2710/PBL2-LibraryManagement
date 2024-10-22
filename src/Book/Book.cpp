#include "Book.h";

Book::Book() {
    this->bookId = 0;
    this->title = "";
    this->author = Author();
    this->publisher = Publisher();
    this->category = Category();
    this->quantity = 0;
    this->publishedDate = Date();
}

Book::Book(int bookId, string& title, Author& author, Publisher& publisher, Category& category, int& quantity, Date& publishedDate) {
    this->bookId = bookId;
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->category = category;
    this->quantity = quantity;
    this->publishedDate = publishedDate;
}

void Book::setBookId(int bookId) {
    this->bookId = bookId;
}

int Book::getBookId() {
    return this->bookId;
}

void Book::setTitle(string title) {
    this->title = title;
}

string Book::getTitle() {
    return this->title;
}

void Book::setAuthor(Author author) {
    this->author = author;
}

Author Book::getAuthor() {
    return this->author;
}

void Book::setPublisher(Publisher publisher) {
    this->publisher = publisher;
}

Publisher Book::getPublisher() {
    return this->publisher;
}

void Book::setCategory(Category category) {
    this->category = category;
}

Category Book::getCategory() {
    return this->category;
}

void Book::setPublishedDate(Date publishedDate) {
    this->publishedDate = publishedDate;
}

Date Book::getPublishedDate() {
    return this->publishedDate;
}

void Book::setQuantity(int quantity) {
    this->quantity = quantity;
}

int Book::getQuantity() {
    return this->quantity;
}

