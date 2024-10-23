#include "CategoryRepository.h"

CategoryRepository* CategoryRepository::_categoryRepository = nullptr;
const char* CategoryRepository::_categoryFileName = _categoryFileName;
const char* CategoryRepository::_categoryTempFileName = _categoryTempFileName;

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
        cerr << "Không thể mở file để ghi." << endl;
        return;
    }

    outFile << category.getCategoryId() << " " 
            << category.getCategoryName() << " "
            << endl;

    outFile.close();
    cout << "Thêm thể loại thành công!" << endl;
}

void CategoryRepository::updateCategory(Category category) {
    ifstream inFile(_categoryFileName);
    ofstream tempFile(_categoryTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << endl;
        return;
    }

    bool found = false;
    int categoryId;
    string categoryName;
    while (inFile >> categoryId >> categoryName) {
        if (categoryId == category.getCategoryId()) {
            tempFile << category.getCategoryId() << "," << category.getCategoryName() << endl;
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
        cout << "Cập nhật thể loại thành công!" << endl;
    } else {
        remove(_categoryTempFileName);
        cout << "Thể loại không tồn tại!" << endl;
    }
}

void CategoryRepository::deleteCategory(int categoryId) {
    ifstream inFile(_categoryFileName);
    ofstream tempFile(_categoryTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << endl;
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
        cout << "Xóa thể loại thành công!" << endl;
    } else {
        remove(_categoryTempFileName);
        cout << "Thể loại không tồn tại!" << endl;
    }
}

Category CategoryRepository::getCategoryById(int categoryId) {
    ifstream inFile(_categoryFileName);
    if (!inFile.is_open()) {
        cerr << "Không thể mở file để đọc." << endl;
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
    cout << "Thể loại không tồn tại!" << endl;
    return Category();
}

