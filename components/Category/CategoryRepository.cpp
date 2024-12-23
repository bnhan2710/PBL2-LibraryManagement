#include "CategoryRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

CategoryRepository* CategoryRepository::_categoryRepository = nullptr;
const char* CategoryRepository::_categoryFileName = "database/Category.txt";
const char* CategoryRepository::_categoryTempFileName = "database/TempCategory.txt";

CategoryRepository::CategoryRepository() {}

CategoryRepository* CategoryRepository::initCategoryRepository() {
    if (_categoryRepository == nullptr) {
        _categoryRepository = new CategoryRepository();
    }
    return _categoryRepository;
}

CategoryRepository::~CategoryRepository() {}

void CategoryRepository::addCategory(const Category& category) {
    ofstream outFile(_categoryFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to write" << endl;
        return;
    }

    outFile << category.getCategoryId() << "|"
            << category.getCategoryName() << "|"
            << category.getNumOfBooks() << endl;

    outFile.close();
    cout << "Add category successful" << endl;
}

void CategoryRepository::updateCategory(const Category& category) {
    ifstream inFile(_categoryFileName);
    ofstream tempFile(_categoryTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, numOfBooksStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, numOfBooksStr, '|');

        int id = atoi(idStr.c_str());

        if (id == category.getCategoryId()) {
            tempFile << category.getCategoryId() << "|"
                     << category.getCategoryName() << "|"
                     << category.getNumOfBooks() << endl;
            found = true;
        } else {
            tempFile << idStr << "|" << name << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_categoryFileName);
        rename(_categoryTempFileName, _categoryFileName);
        cout << "Updated category successfully" << endl;
    } else {
        remove(_categoryTempFileName);
        cout << "Category not found" << endl;
    }
}

void CategoryRepository::deleteCategory(int categoryId) {
    ifstream inFile(_categoryFileName);
    ofstream tempFile(_categoryTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, numOfBooksStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, numOfBooksStr, '|');

        int id = atoi(idStr.c_str());

        if (id == categoryId) {
            found = true;
        } else {
            tempFile << idStr << "|" 
                     << name << "|"
                     << numOfBooksStr << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_categoryFileName);
        rename(_categoryTempFileName, _categoryFileName);
        cout << "Deleted category successfully" << endl;
    } else {
        remove(_categoryTempFileName);
        cout << "Category not found" << endl;
    }
}

Category CategoryRepository::getCategoryById(int categoryId) {
    ifstream inFile(_categoryFileName);
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return Category();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, numOfBooksStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, numOfBooksStr, '|');

        int id = atoi(idStr.c_str());

        if (id == categoryId) {
            inFile.close();
            return Category(id, name, atoi(numOfBooksStr.c_str()));
        }
    }

    inFile.close();
    cout << "Category not found" << endl;
    return Category();
}

List<Category> CategoryRepository::getAllCategories() {
    ifstream inFile(_categoryFileName);
    List<Category> categories;
    if (!inFile.is_open()) {
        cerr << "Can't not open file to read" << endl;
        return categories;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, numOfBooksStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, numOfBooksStr, '|');

        int id = atoi(idStr.c_str());

        categories.InsertLast(Category(id, name, atoi(numOfBooksStr.c_str())));
    }

    inFile.close();
    return categories;
}
