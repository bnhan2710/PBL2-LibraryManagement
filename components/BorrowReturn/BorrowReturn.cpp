#include "BorrowReturn.h"
enum Status {
    BORROWED,
    RETURNED
};

BorrowReturn::BorrowReturn(){
}

BorrowReturn::BorrowReturn(int id, int userId, int bookId, Date borrowAt, int num_of_days, Status status){
    this->id = id;
    this->userId = userId;
    this->bookId = bookId;
    this->borrowAt = borrowAt;
    this->num_of_days = num_of_days;
    this->status = Status::BORROWED;
}

BorrowReturn::~BorrowReturn(){

}

Date BorrowReturn::getBorrowAt(){
    return this->borrowAt;
}
Date BorrowReturn::getReturnAt(){
    Date returnAt = this->borrowAt;
    for(int i = 0; i < this->num_of_days; i++){
        returnAt.nextDay();
    }
    return returnAt;
}


int BorrowReturn::getNumOfDays(){
    return this->num_of_days;
}

int BorrowReturn::getId(){
    return this->id;
}

Status BorrowReturn::getStatus(){
    return this->status;
}

void BorrowReturn::setStatus(Status status){
    this->status = status;
}

void BorrowReturn::setNumOfDays(int num_of_days){
    this->num_of_days = num_of_days;
}

