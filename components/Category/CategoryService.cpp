#include "CategoryService.h"

CategoryService* CategoryService::_categoryService = nullptr;
string categoryName;
int categoryId;

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

void CategoryService::addCategory() {
    categoryId = this->_categoriesList.GetLength() + 1;
    cin.ignore();
    cout << "Enter category name: ";
    cin >> categoryName;
    cin.ignore();
    Category category(categoryId, categoryName);
    this->_categoriesList.InsertLast(category);
    this->_categoriesRepository->addCategory(category);
}

void CategoryService::updateCategory() {
    cout << "Enter category ID: ";
    cin >> categoryId;
    cin.ignore();
    Category isExistedCategory = this->_categoriesRepository->getCategoryById(categoryId);
    if (isExistedCategory.getCategoryId() == 0) {
        return;
    }
    int categoryChoice;
    do {
        cout << "=====================================\n";
        cout << "1. Update categoryName" << endl;
        cout << "2. Exit" << endl;
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> categoryChoice;

        switch (categoryChoice) {
            case 1:
                cout << "Enter new categoryName: ";
                cin >> categoryName;
                cin.ignore();
                isExistedCategory.setCategoryName(categoryName);
                break;
            case 2: 
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (categoryChoice != 2);
    this->_categoriesRepository->updateCategory(isExistedCategory);
}

void CategoryService::deleteCategory() {
    cout << "Enter category ID: ";
    cin >> categoryId;
    cin.ignore();
    Category isExistedCategory = this->_categoriesRepository->getCategoryById(categoryId);
    if (isExistedCategory.getCategoryId() == 0) {
        return;
    }
    isExistedCategory.setCategoryName("Deleted");
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