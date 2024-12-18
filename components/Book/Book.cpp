#include "Book.h"
#include <iostream>
#include <string>

Book::Book(){
}

Book::Book(int bookId, string code, string title, Author& author, Category& category, Publisher& publisher, int quantity){
    this->bookId = bookId;
    this->code = code;
    this->title = title;
    this->author = author;
    this->category = category;
    this->publisher = publisher;
    this->quantity = quantity;
    this->publisherId = publisher.getPublisherId();
    this->categoryId = category.getCategoryId();
}

Book::~Book(){

}

/* Book::Book(int bookId, string code, string title, string author, string category, string publisher, int quantity){ */
/*     this->bookId = bookId; */
/*     this->code = code; */
/*     this->title = title; */
/*     this->author = author; */
/*     this->category = category; */
/*     this->publisher = publisher; */
/*     this->quantity = quantity; */
/* } */

void Book::setBookId(int bookId){
    this->bookId = bookId;
}

int Book::getBookId() const {
    return this->bookId;
}

void Book::setTitle(string title){
    this->title = title;
}

string Book::getTitle() const {
    return this->title;
}

void Book::setAuthor(Author& author){
    this->author = author;
}

Author Book::getAuthor() const {
    return this->author;
}

void Book::setCategory(Category& category){
    this->category = category;
}

Category Book::getCategory() const {
    return this->category;
}

void Book::setPublisher(Publisher& publisher){
    this->publisher = publisher;
}

Publisher Book::getPublisher() const {
    return this->publisher;
}

/* void Book::setAuthor(string author){ */
/*     this->author = author; */
/* } */

/* string Book::getAuthor() const { */
/*     return this->author; */
/* } */

/* void Book::setPublisher(string publisher){ */
/*     this->publisher = publisher; */
/* } */

/* string Book::getPublisher() const { */
/*     return this->publisher; */
/* } */

/* void Book::setCategory(string category){ */
/*     this->category = category; */
/* } */

/* string Book::getCategory() const { */
/*     return this->category; */
/* } */

void Book::setCode(string code){
    this->code = code;
}

string Book::getCode() const {
    return this->code;
}

void Book::setQuantity(int quantity){
    this->quantity = quantity;
}

int Book::getQuantity() const {
    return this->quantity;
}

void Book::setNumOfPages(int num_of_pages){
    this->num_of_pages = num_of_pages;
}

int Book::getNumOfPages() const {
    return this->num_of_pages;
}

void Book::setPublisherId(int publisherId){
    this->publisherId = publisherId;
}

int Book::getPublisherId() const {
    return this->publisherId;
}

void Book::setCategoryId(int categoryId){
    this->categoryId = categoryId;
}

int Book::getCategoryId() const {
    return this->categoryId;
}


