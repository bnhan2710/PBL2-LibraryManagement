#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H
#include "Category.h"
#include "CategoryRepository.h"
class CategoryService {
private:
    static CategoryService* _categoryService;
    CategoryRepository* _categoriesRepository;
    CategoryService();
public:
    static CategoryService* initCategoryService();
    ~CategoryService();
    void addCategory(Category category);
    void updateCategory(Category category);
    void deleteCategory(int categoryId);
    Category getCategoryById(int categoryId);
};
#endif
