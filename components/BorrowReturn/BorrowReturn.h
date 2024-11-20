#ifndef BORROWRETURN_H
#define BORROWRETURN_H
#include <string>
#include "../User/User.h"
#include "../Book/Book.h"
#include "../../utils/date/date.h"
using namespace std;
enum Status {
    BORROWING,
    RETURNED
};
class BorrowReturn {
private:
    int id;
    int userId;
    int bookId;
    Date borrowAt;
    Date returnAt;
    int num_of_days;
    Status status;
public:
    BorrowReturn();
    BorrowReturn(int, int, int, Date,Date, int, Status);
    ~BorrowReturn();
    Date getBorrowAt();
    Date getReturnAt();
    int getQuantity();
    int getNumOfDays();
    int getId();
    Status getStatus();
    void setStatus(Status);
    void setNumOfDays(int); 
};  
#endif