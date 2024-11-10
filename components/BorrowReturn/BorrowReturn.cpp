#include "BorrowReturn.h"

BorrowReturn::BorrowReturn() {
    this->borrowReturnId = 0;
    this->user = User();
    this->book = Book();
    this->borrowDate = Date();
    this->returnDate = Date();
    this->status = "";
}

BorrowReturn::BorrowReturn(int borrowReturnId, User& user, Book& book, Date& borrowDate, Date& returnDate, string& status) {
    this->borrowReturnId = borrowReturnId;
    this->user = user;
    this->book = book;
    this->borrowDate = borrowDate;
    this->returnDate = returnDate;
    this->status = status;
}

void BorrowReturn::setBorrowReturnId(int borrowReturnId) {
    this->borrowReturnId = borrowReturnId;
}

int BorrowReturn::getBorrowReturnId() {
    return this->borrowReturnId;
}

void BorrowReturn::setUser(User user) {
    this->user = user;
}

User BorrowReturn::getUser() {
    return this->user;
}

void BorrowReturn::setBook(Book book) {
    this->book = book;
}

Book BorrowReturn::getBook() {
    return this->book;
}

void BorrowReturn::setBorrowDate(Date borrowDate) {
    this->borrowDate = borrowDate;
}

Date BorrowReturn::getBorrowDate() {
    return this->borrowDate;
}

void BorrowReturn::setReturnDate(Date returnDate) {
    this->returnDate = returnDate;
}

Date BorrowReturn::getReturnDate() {
    return this->returnDate;
}

void BorrowReturn::setStatus(string status) {
    this->status = status;
}

string BorrowReturn::getStatus() {
    return this->status;
}
