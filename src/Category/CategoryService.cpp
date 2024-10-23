#include "CategoryService.h"

CategoryService* CategoryService::_categoryService = nullptr;

CategoryService::CategoryService() {
    this->_categoriesRepository = CategoryRepository::initCategoryRepository();
}

CategoryService* CategoryService::initCategoryService() {
    if ( _categoryService == nullptr ) {
        _categoryService = new CategoryService();
    }
    return _categoryService;
}

CategoryService::~CategoryService() {
}

void CategoryService::addCategory(Category category) {
    this->_categoriesRepository->addCategory(category);
}

void CategoryService::updateCategory(Category category) {
    this->_categoriesRepository->updateCategory(category);
}

void CategoryService::deleteCategory(int categoryId) {
    this->_categoriesRepository->deleteCategory(categoryId);
}

Category CategoryService::getCategoryById(int categoryId) {
    return this->_categoriesRepository->getCategoryById(categoryId);
}