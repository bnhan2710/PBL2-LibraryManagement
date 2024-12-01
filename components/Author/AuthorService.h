#ifndef AUTHORSERVICE_H
#define AUTHORSERVICE_H
#include "Author.h"
#include "AuthorRepository.h"
#include "../../utils/List.h"
using namespace std;
class AuthorService {
private:
    static AuthorService* _authorService;
    AuthorRepository* _authorRepository;
    List<Author> _authorList;
    AuthorService();
public:
    static AuthorService* initAuthorService();
    ~AuthorService();
    void addAuthor(const string& authorName, const Date& birthDate, const string& authorInfo);
    void updateAuthor(int authorId, const string& authorName, const Date& birthDate, const string& authorInfo);
    void deleteAuthor(int authorId);
    List<Author> getAuthor( int authorId );
    List<Author> getAuthor();
};
#endif
