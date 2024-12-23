#include "CategoryService.h"

CategoryService* CategoryService::_categoryService = nullptr;

CategoryService::CategoryService() {
    this->_categoriesRepository = CategoryRepository::initCategoryRepository();
    this->_categoriesList = this->_categoriesRepository->getAllCategories();
}

CategoryService* CategoryService::initCategoryService() {
    if ( _categoryService == nullptr ) {
        _categoryService = new CategoryService();
    }
    return _categoryService;
}

CategoryService::~CategoryService() {
}

void CategoryService::addCategory(const string& categoryName) {
    int categoryId = this->_categoriesList.GetLength() + 1;

    Category category(categoryId, categoryName, 0);

    this->_categoriesList.InsertLast(category);
    this->_categoriesRepository->addCategory(category);
}

void CategoryService::updateCategory(int categoryId, const string& categoryName) {
    Category isExistedCategory = this->_categoriesRepository->getCategoryById(categoryId);
    if (isExistedCategory.getCategoryId() == 0) {
        return;
    }
    isExistedCategory.setCategoryName(categoryName);
    this->_categoriesRepository->updateCategory(isExistedCategory);
}

void CategoryService::deleteCategory(int categoryId) {
    Category isExistedCategory = this->_categoriesRepository->getCategoryById(categoryId);
    if (isExistedCategory.getCategoryId() == 0) {
        return;
    }
    isExistedCategory.setCategoryName("0");
    isExistedCategory.setNumOfBooks(0);
    this->_categoriesRepository->updateCategory(isExistedCategory);
}

List<Category> CategoryService::getCategory( int categoryId ) {
    List<Category> categories;
    Category category = this->_categoriesRepository->getCategoryById(categoryId);
    categories.InsertLast(category);
    return categories;
}

List<Category> CategoryService::getCategory() {
    return this->_categoriesRepository->getAllCategories();
}
