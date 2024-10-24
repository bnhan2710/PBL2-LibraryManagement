#ifndef AUTHOR_H
#define AUTHOR_H
#include <string>
using namespace std;
#ifndef DATE
#define DATE
struct Date {
    int day;
    int month;
    int year;
};
#endif
class Author {
private:
    int authorId;
    string authorName;
    Date birthDate;
    string authorInfo;
public:
    Author();
    Author(int authorId, string& authorName, Date& birthDate, string& authorInfo);
    void setAuthorId(int authorId);
    int getAuthorId();
    void setAuthorName(string authorName);
    string getAuthorName();
    void setBirthDate(Date birthDate);
    Date getBirthDate();
    void setAuthorInfo(string authorInfo);
    string getAuthorInfo();
};
#endif
