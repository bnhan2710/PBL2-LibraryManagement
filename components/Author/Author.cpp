#include "Author.h"

Author::Author() {
    this->authorId = 0;
    this->authorName = "";
    this->authorInfo = "";
}

Author::Author(int authorId, const string& authorName, const Date& birthDate, const string& authorInfo) {
    this->authorId = authorId;
    this->authorName = authorName;
    this->authorInfo = authorInfo;
    this->birthDate = birthDate;
}

void Author::setAuthorId(int authorId) {
    this->authorId = authorId;
}

int Author::getAuthorId() const {
    return this->authorId;
}

void Author::setAuthorName(string authorName) {
    this->authorName = authorName;
}

string Author::getAuthorName() const {
    return this->authorName;
}

void Author::setAuthorInfo(string authorInfo) {
    this->authorInfo = authorInfo;
}

string Author::getAuthorInfo() const {
    return this->authorInfo;
}

void Author::setBirthDate(Date birthDate) {
    this->birthDate = birthDate;
}

Date Author::getBirthDate() const {
    return this->birthDate;
}

