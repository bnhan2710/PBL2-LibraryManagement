#include "AuthorService.h"

AuthorService* AuthorService::_authorService = nullptr;

AuthorService::AuthorService() {
    this->_authorRepository = AuthorRepository::initAuthorRepository();
    this->_authorList = this->_authorRepository->getAllAuthors();
}

AuthorService* AuthorService::initAuthorService() {
    if ( _authorService == nullptr ) {
        _authorService = new AuthorService();
    }
    return _authorService;
}

AuthorService::~AuthorService() {
}

void AuthorService::addAuthor(const string& authorName, const Date& birthDate, const string& authorInfo) {
    int authorId = this->_authorList.GetLength() + 1;

    Author author(authorId, authorName, birthDate, authorInfo);

    this->_authorList.InsertLast(author);
    this->_authorRepository->addAuthor(author);
}

void AuthorService::updateAuthor(int authorId, const string& authorName, const Date& birthDate, const string& authorInfo) {
    Author isExistedAuthor = this->_authorRepository->getAuthorById(authorId);
    if (isExistedAuthor.getAuthorId() == 0) {
        return;
    }
    isExistedAuthor.setAuthorName(authorName);
    isExistedAuthor.setBirthDate(birthDate);
    isExistedAuthor.setAuthorInfo(authorInfo);
    this->_authorRepository->updateAuthor(isExistedAuthor);
}

void AuthorService::deleteAuthor(int authorId) {
    Author isExistedAuthor = this->_authorRepository->getAuthorById(authorId);
    if (isExistedAuthor.getAuthorId() == 0) {
        return;
    }
    isExistedAuthor.setAuthorName("0");
    isExistedAuthor.setBirthDate(Date(0, 0, 0));
    isExistedAuthor.setAuthorInfo("0");
    this->_authorRepository->updateAuthor(isExistedAuthor);
}

List<Author> AuthorService::getAuthor( int authorId ) {
    List<Author> authors;
    Author author = this->_authorRepository->getAuthorById(authorId);
    authors.InsertLast(author);
    return authors;
}

List<Author> AuthorService::getAuthor() {
    return this->_authorRepository->getAllAuthors();
}
