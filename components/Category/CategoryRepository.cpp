#include "CategoryRepository.h"

CategoryRepository* CategoryRepository::_categoryRepository = nullptr;
const char* CategoryRepository::_categoryFileName = "database/Category.txt";
const char* CategoryRepository::_categoryTempFileName = "database/TempCategory.txt";

CategoryRepository::CategoryRepository() {
}

CategoryRepository* CategoryRepository::initCategoryRepository() {
    if (_categoryRepository == nullptr) {
        _categoryRepository = new CategoryRepository();
    }
    return _categoryRepository;
}

CategoryRepository::~CategoryRepository() {
}

void CategoryRepository::addCategory(Category category) {
    ofstream outFile;
    outFile.open(_categoryFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    outFile << category.getCategoryId() << " " 
            << category.getCategoryName() << " "
            << endl;

    outFile.close();
    cout << "Add category successful" << endl;
}

void CategoryRepository::updateCategory(Category category) {
    ifstream inFile(_categoryFileName);
    ofstream tempFile(_categoryTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    bool found = false;
    int categoryId;
    string categoryName;
    while (inFile >> categoryId >> categoryName) {
        if (categoryId == category.getCategoryId()) {
            tempFile << category.getCategoryId() << " " << category.getCategoryName() << endl;
            found = true;
        } else {
            tempFile << categoryId << " " 
                     << categoryName << " "
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_categoryFileName);
        rename(_categoryTempFileName, _categoryFileName);
        cout << "Updated category successful" << endl;
    } else {
        remove(_categoryTempFileName);
        cout << "Category not found" << endl;
    }
}

void CategoryRepository::deleteCategory(int categoryId) {
    ifstream inFile(_categoryFileName);
    ofstream tempFile(_categoryTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    bool found = false;
    int CategoryId;
    string CategoryName;
    while (inFile >> CategoryId >> CategoryName) {
        if (CategoryId == categoryId) {
            found = true;
        } else {
            tempFile << CategoryId << " " 
                     << CategoryName << " " 
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_categoryFileName);
        rename(_categoryTempFileName, _categoryFileName);
        cout << "Deleted category successful" << endl;
    } else {
        remove(_categoryTempFileName);
        cout << "Category not found" << endl;
    }
}

Category CategoryRepository::getCategoryById(int categoryId) {
    ifstream inFile(_categoryFileName);
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return Category();
    }
    int CategoryId;
    string CategoryName;
    while (inFile >> CategoryId >> CategoryName) {
        if (CategoryId == categoryId) {
            inFile.close();
            return Category(CategoryId, CategoryName);
        }
    }
    inFile.close();
    cout << "CategoryId not found" << endl;
    return Category();
}

List<Category> CategoryRepository::getAllCategories() {
    ifstream inFile(_categoryFileName);
    List<Category> categories;
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return categories;
    }
    int CategoryId;
    string CategoryName;
    while (inFile >> CategoryId >> CategoryName) {
        categories.InsertLast(Category(CategoryId, CategoryName));
    }
    inFile.close();
    return categories;
}
