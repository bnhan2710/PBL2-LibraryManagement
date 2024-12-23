#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
using namespace std;
class Category {
private:
    int categoryId;
    string categoryName;
    int numOfBooks;
public:
    Category();
    Category(int categoryId,const string& categoryName, int numOfBooks);
    void setCategoryId(int categoryId);
    int getCategoryId() const;
    void setCategoryName(string categoryName);
    string getCategoryName() const;
    void setNumOfBooks(int numOfBooks);
    int getNumOfBooks() const;
};
#endif
