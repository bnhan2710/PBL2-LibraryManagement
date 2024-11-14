#ifndef BORROWRETURN_H
#define BORROWRETURN_H
#include <string>
#include "../User/User.h"
#include "../Book/Book.h"
#include "../../utils/date/date.h"
using namespace std;
enum Status {
    BORROWED,
    RETURNED
};
class BorrowReturn {
private:
    int id;
    int userId;
    int bookId;
    Date borrowAt;
    int num_of_days;
    Status status;
public:
    BorrowReturn();
    BorrowReturn(int id, int userId, int bookId, Date borrowAt, int num_of_days, Status status);
    ~BorrowReturn();
    Date getBorrowAt();
    Date getReturnAt();
    int getQuantity();
    int getNumOfDays();
    int getId();
    Status getStatus();
    void setStatus(Status status);
    void setNumOfDays(int num_of_days); 
};  
#endif