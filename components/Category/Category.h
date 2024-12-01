#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
using namespace std;
class Category {
private:
    int categoryId;
    string categoryName;
public:
    Category();
    Category(int categoryId,const string& categoryName);
    void setCategoryId(int categoryId);
    int getCategoryId() const;
    void setCategoryName(string categoryName);
    string getCategoryName() const;
};
#endif
