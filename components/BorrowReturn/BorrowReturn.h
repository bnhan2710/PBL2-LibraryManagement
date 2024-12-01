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
    Date getBorrowAt() const;
    void setBorrowAt(Date);
    Date getReturnAt() const;
    void setReturnAt(Date);
    int getQuantity() const;
    void setQuantity(int);
    int getNumOfDays() const;
    void setNumOfDays(int); 
    int getId() const;
    void setId(int);
    Status getStatus() const;
    void setStatus(Status);
    int getUserId() const;
    void setUserId(int);
    int getBookId() const;
    void setBookId(int);
};  
#endif
