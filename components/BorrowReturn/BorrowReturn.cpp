#include "BorrowReturn.h"
enum Status {
    BORROWED,
    RETURNED
};

BorrowReturn::BorrowReturn(){
}

BorrowReturn::BorrowReturn(int id, int userId, int bookId, Date borrowAt, Date returnAt, int num_of_days, Status status)

        : id(id), userId(userId), bookId(bookId), borrowAt(borrowAt), returnAt(returnAt), num_of_days(num_of_days), status(status) {}
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

