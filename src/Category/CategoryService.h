#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H
#include "Category.h"
#include "CategoryRepository.h"
#include "../../utils/List.h"
class CategoryService {
private:
    static CategoryService* _categoryService;
    CategoryRepository* _categoriesRepository;
    List<Category> _categoriesList;
    CategoryService();
public:
    static CategoryService* initCategoryService();
    ~CategoryService();
    void addCategory();
    void updateCategory();
    void deleteCategory();
    Category getCategoryById();
};
#endif
