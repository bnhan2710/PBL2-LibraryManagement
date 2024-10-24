#include "Author.h"

Author::Author() {
    this->authorId = 0;
    this->authorName = "";
    this->authorInfo = "";
}

Author::Author(int authorId, string& authorName, Date& birthDate, string& authorInfo) {
    this->authorId = authorId;
    this->authorName = authorName;
    this->authorInfo = authorInfo;
    this->birthDate = birthDate;
}

void Author::setAuthorId(int authorId) {
    this->authorId = authorId;
}

int Author::getAuthorId() {
    return this->authorId;
}

void Author::setAuthorName(string authorName) {
    this->authorName = authorName;
}

string Author::getAuthorName() {
    return this->authorName;
}

void Author::setAuthorInfo(string authorInfo) {
    this->authorInfo = authorInfo;
}

string Author::getAuthorInfo() {
    return this->authorInfo;
}

void Author::setBirthDate(Date birthDate) {
    this->birthDate = birthDate;
}

Date Author::getBirthDate() {
    return this->birthDate;
}

