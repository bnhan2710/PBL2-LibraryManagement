#include "Book.h"
#include <iostream>
#include <string>

Book::Book(){
}

/* Book::Book(int bookId, string title, Author author, int quantity, int num_of_pages, int publisherId, int categoryId){ */
/*     this->bookId = bookId; */
/*     this->title = title; */
/*     this->author = author; */
/*     this->quantity = quantity; */
/*     this->num_of_pages = num_of_pages; */
/*     this->publisherId = publisherId; */
/*     this->categoryId = categoryId; */
/* } */

Book::~Book(){

}

Book::Book(int bookId, string code, string title, string author, string category, string publisher, int quantity){
    this->bookId = bookId;
    this->code = code;
    this->title = title;
    this->author = author;
    this->category = category;
    this->publisher = publisher;
    this->quantity = quantity;
}

void Book::setBookId(int bookId){
    this->bookId = bookId;
}

int Book::getBookId(){
    return this->bookId;
}

void Book::setTitle(string title){
    this->title = title;
}

string Book::getTitle(){
    return this->title;
}

/* void Book::setAuthor(Author author){ */
/*     this->author = author; */
/* } */

/* Author Book::getAuthor(){ */
/*     return this->author; */
/* } */

/* void Book::setCategory(Category category){ */
/*     this->category = category; */
/* } */

/* Category Book::getCategory(){ */
/*     return this->category; */
/* } */

/* void Book::setPublisher(Publisher publisher){ */
/*     this->publisher = publisher; */
/* } */

/* Publisher Book::getPublisher(){ */
/*     return this->publisher; */
/* } */

void Book::setAuthor(string author){
    this->author = author;
}

string Book::getAuthor(){
    return this->author;
}

void Book::setPublisher(string publisher){
    this->publisher = publisher;
}

string Book::getPublisher(){
    return this->publisher;
}

void Book::setCategory(string category){
    this->category = category;
}

string Book::getCategory(){
    return this->category;
}

void Book::setCode(string code){
    this->code = code;
}

string Book::getCode(){
    return this->code;
}

void Book::setQuantity(int quantity){
    this->quantity = quantity;
}

int Book::getQuantity(){
    return this->quantity;
}

void Book::setNumOfPages(int num_of_pages){
    this->num_of_pages = num_of_pages;
}

int Book::getNumOfPages(){
    return this->num_of_pages;
}

void Book::setPublisherId(int publisherId){
    this->publisherId = publisherId;
}

int Book::getPublisherId(){
    return this->publisherId;
}

void Book::setCategoryId(int categoryId){
    this->categoryId = categoryId;
}

int Book::getCategoryId(){
    return this->categoryId;
}


