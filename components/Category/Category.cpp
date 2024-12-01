#include "Category.h"

Category::Category() {
    this->categoryId = 0;
    this->categoryName = "";
}

Category::Category(int categoryId, const string& categoryName) {
    this->categoryId = categoryId;
    this->categoryName = categoryName;
}

void Category::setCategoryId(int categoryId) {
    this->categoryId = categoryId;
}

int Category::getCategoryId() const {
    return this->categoryId;
}

void Category::setCategoryName(string categoryName) {
    this->categoryName = categoryName;
}

string Category::getCategoryName() const {
    return this->categoryName;
}
