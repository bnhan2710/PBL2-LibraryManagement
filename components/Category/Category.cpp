#include "Category.h"

Category::Category() {
    this->categoryId = 0;
    this->categoryName = "";
    this->numOfBooks = 0;
}

Category::Category(int categoryId, const string& categoryName, int numOfBooks) {
    this->categoryId = categoryId;
    this->categoryName = categoryName;
    this->numOfBooks = numOfBooks;
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

void Category::setNumOfBooks(int numOfBooks) {
    this->numOfBooks = numOfBooks;
}

int Category::getNumOfBooks() const {
    return this->numOfBooks;
}
