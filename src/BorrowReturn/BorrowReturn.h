#ifndef BORROWRETURN_H
#define BORROWRETURN_H
#include <string>
#include "User.h"
#include "Book.h"
using namespace std;
struct Date {
    int day;
    int month;
    int year;
};
class BorrowReturn {
private:
    int borrowReturnId;
    User user;
    Book book;
    Date borrowDate;
    Date returnDate;
    string status;
public:
    BorrowReturn();
    BorrowReturn(int borrowReturnId, User user, Book book, Date borrowDate, Date returnDate, string status);
    void setBorrowReturnId(int borrowReturnId);
    int getBorrowReturnId();
    void setUser(User user);
    User getUser();
    void setBook(Book book);
    Book getBook();
    void setBorrowDate(Date borrowDate);
    Date getBorrowDate();
    void setReturnDate(Date returnDate);
    Date getReturnDate();
    void setStatus(string status);
    string getStatus();
};
#endif