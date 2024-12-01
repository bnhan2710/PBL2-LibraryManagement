#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H
#include "Category.h"
#include <iostream>
#include <fstream>
#include "../../utils/List.h"
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
    void addCategory(const Category& category);
    void updateCategory(const Category& category);
    void deleteCategory(int categoryId);
    Category getCategoryById(int categoryId);
    List<Category> getAllCategories();
};
#endif
