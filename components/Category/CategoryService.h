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
    void addCategory(const string&);
    void updateCategory(const int, const string&);
    void deleteCategory(const int);
    List<Category> getCategory( int );
    List<Category> getCategory();
};
#endif
