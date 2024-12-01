#ifndef AUTHORREPOSITORY_H
#define AUTHORREPOSITORY_H
#include "Author.h"
#include <iostream>
#include <fstream>
#include "../../utils/List.h"
using namespace std;
class AuthorRepository {
private:
    static AuthorRepository* _authorRepository;
    static const char* _authorFileName;
    static const char* _authorTempFileName;
    AuthorRepository();

public:
    static AuthorRepository *initAuthorRepository();
    ~AuthorRepository();
    void addAuthor(const Author& author);
    void updateAuthor(const Author& author);
    void deleteAuthor(int authorId);
    Author getAuthorById(int authorId);
    List<Author> getAllAuthors();
};
#endif
