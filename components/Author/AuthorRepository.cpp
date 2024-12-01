#include "AuthorRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

AuthorRepository* AuthorRepository::_authorRepository = nullptr;
const char* AuthorRepository::_authorFileName = "database/Author.txt";
const char* AuthorRepository::_authorTempFileName = "database/TempAuthor.txt";

AuthorRepository::AuthorRepository() {}

AuthorRepository* AuthorRepository::initAuthorRepository() {
    if (_authorRepository == nullptr) {
        _authorRepository = new AuthorRepository();
    }
    return _authorRepository;
}

AuthorRepository::~AuthorRepository() {}

void AuthorRepository::addAuthor(const Author& author) {
    ofstream outFile(_authorFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't open file to write" << endl;
        return;
    }

    outFile << author.getAuthorId() << "|"
            << author.getAuthorName() << "|"
            << author.getBirthDate().getFormattedDate() << "|"
            << author.getAuthorInfo() << endl;

    outFile.close();
    cout << "Add author successful" << endl;
}

void AuthorRepository::updateAuthor(const Author& author) {
    ifstream inFile(_authorFileName);
    ofstream tempFile(_authorTempFileName, ios::out);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, birthDateStr, info;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, birthDateStr, '|');
        getline(ss, info);

        int id = atoi(idStr.c_str());

        if (id == author.getAuthorId()) {
            tempFile << author.getAuthorId() << "|"
                     << author.getAuthorName() << "|"
                     << author.getBirthDate().getFormattedDate() << "|"
                     << author.getAuthorInfo() << endl;
            found = true;
        } else {
            tempFile << idStr << "|"
                     << name << "|"
                     << birthDateStr << "|"
                     << info << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_authorFileName);
        rename(_authorTempFileName, _authorFileName);
        cout << "Updated author successful" << endl;
    } else {
        remove(_authorTempFileName);
        cout << "Author not found" << endl;
    }
}

void AuthorRepository::deleteAuthor(int authorId) {
    ifstream inFile(_authorFileName);
    ofstream tempFile(_authorTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't open file to read and write" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, birthDateStr, info;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, birthDateStr, '|');
        getline(ss, info);

        if (atoi(id.c_str()) == authorId) {
            found = true;  
        } else {
            tempFile << id << "|"
                     << name << "|"
                     << birthDateStr << "|"
                     << info << endl;
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_authorFileName);
        rename(_authorTempFileName, _authorFileName);
        cout << "Deleted author successful" << endl;
    } else {
        remove(_authorTempFileName);
        cout << "Author not found" << endl;
    }
}

Author AuthorRepository::getAuthorById(int authorId) {
    ifstream inFile(_authorFileName);
    if (!inFile.is_open()) {
        cerr << "Can't open file to read" << endl;
        return Author();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, birthDateStr, info;
        int day, month, year, cnt = 0;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, birthDateStr, '|');
        getline(ss, info);

        int id = atoi(idStr.c_str());
        if (id == authorId) {
            for( int i = 0; i < birthDateStr.length(); i++ ) {
                if ( birthDateStr[i] == '-' && cnt == 0 ) {
                    day = atoi(birthDateStr.substr(0, i).c_str());
                    cnt = i + 1;
                } else if ( birthDateStr[i] == '-' && cnt != 0 ) {
                    month = atoi(birthDateStr.substr(cnt, i).c_str());
                    year = atoi(birthDateStr.substr(i+1, birthDateStr.length()).c_str());
                }
            }
            Date birthDate = Date(day, month, year);
            return Author(id, name, birthDate, info);
        }
    }

    inFile.close();
    cout << "Author not found" << endl;
    return Author();
}

List<Author> AuthorRepository::getAllAuthors() {
    ifstream inFile(_authorFileName);
    List<Author> authorList;
    if (!inFile.is_open()) {
        cerr << "Can't open file to read" << endl;
        return authorList;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, birthDateStr, info;
        int day, month, year, cnt = 0;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, birthDateStr, '|');
        getline(ss, info);

        int id = atoi(idStr.c_str());
        for( int i = 0; i < birthDateStr.length(); i++ ) {
            if ( birthDateStr[i] == '-' && cnt == 0 ) {
                day = atoi(birthDateStr.substr(0, i).c_str());
                cnt = i + 1;
            } else if ( birthDateStr[i] == '-' && cnt != 0 ) {
                month = atoi(birthDateStr.substr(cnt, i).c_str());
                year = atoi(birthDateStr.substr(i+1, birthDateStr.length()).c_str());
            }
        }
        cnt = 0;
        Date birthDate = Date(day, month, year);
        authorList.InsertLast(Author(id, name, birthDate, info));
    }

    inFile.close();
    return authorList;
}
