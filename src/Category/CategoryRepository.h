#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H
#include "Category.h"
#include <iostream>
#include <fstream>
using namespace std;
class CategoryRepository {
private:
    static CategoryRepository* _categoryRepository;
    static const char* _categoryFileName;
    static const char* _categoryTempFileName;
    CategoryRepository();

public:
    static CategoryRepository *initCategoryRepository();
    ~CategoryRepository();
    void addCategory(Category category);
    void updateCategory(Category category);
    void deleteCategory(int categoryId);
    Category getCategoryById(int categoryId);
};
#endif