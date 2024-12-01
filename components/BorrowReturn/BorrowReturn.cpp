#include "BorrowReturn.h"

BorrowReturn::BorrowReturn(){
}

BorrowReturn::BorrowReturn(int id, int userId, int bookId, Date borrowAt, Date returnAt, int num_of_days, Status status)

        : id(id), userId(userId), bookId(bookId), borrowAt(borrowAt), returnAt(returnAt), num_of_days(num_of_days), status(status) {}
BorrowReturn::~BorrowReturn(){

}

Date BorrowReturn::getBorrowAt() const {
    return this->borrowAt;
}
Date BorrowReturn::getReturnAt() const {
    Date returnAt = this->borrowAt;
    for(int i = 0; i < this->num_of_days; i++){
        returnAt.nextDay();
    }
    return returnAt;
}

void BorrowReturn::setBorrowAt(Date borrowAt){
    this->borrowAt = borrowAt;
}

void BorrowReturn::setReturnAt(Date returnAt){
    this->returnAt = returnAt;
}

int BorrowReturn::getNumOfDays() const {
    return this->num_of_days;
}

void BorrowReturn::setNumOfDays(int num_of_days){
    this->num_of_days = num_of_days;
}

int BorrowReturn::getId() const {
    return this->id;
}

void BorrowReturn::setId(int id){
    this->id = id;
}

Status BorrowReturn::getStatus() const {
    return this->status;
}

void BorrowReturn::setStatus(Status status){
    this->status = status;
}

int BorrowReturn::getUserId() const {
    return this->userId;
}

void BorrowReturn::setUserId(int userId){
    this->userId = userId;
}

int BorrowReturn::getBookId() const {
    return this->bookId;
}

void BorrowReturn::setBookId(int bookId){
    this->bookId = bookId;
}
