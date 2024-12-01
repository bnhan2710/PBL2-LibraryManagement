#ifndef AUTHOR_H
#define AUTHOR_H
#include <string>
#include "../utils/date/date.h"
using namespace std;
class Author {
private:
    int authorId;
    string authorName;
    Date birthDate;
    string authorInfo;
public:
    Author();
    Author(int authorId, const string& authorName, const Date& birthDate, const string& authorInfo);
    void setAuthorId(int authorId);
    int getAuthorId() const;
    void setAuthorName(string authorName);
    string getAuthorName() const;
    void setBirthDate(Date birthDate);
    Date getBirthDate() const;
    void setAuthorInfo(string authorInfo);
    string getAuthorInfo() const;
};
#endif
