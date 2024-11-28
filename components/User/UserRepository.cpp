#include "UserRepository.h"
#include "../Role/Member.h"
#include "../Role/Admin.h"
#include "../Role/Librarian.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

UserRepository* UserRepository::_userRepository = nullptr;
const char* UserRepository::_userFileName = "database/User.txt";
const char* UserRepository::_userTempFileName = "database/TempUser.txt";

UserRepository::UserRepository() {}

UserRepository* UserRepository::initUserRepository() {
    if (_userRepository == nullptr) {
        _userRepository = new UserRepository();
    }
    return _userRepository;
}

UserRepository::~UserRepository() {}

void UserRepository::addUser(const User& user) {
    ofstream outFile(_userFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't open file to write" << endl;
        return;
    }

    outFile << user.getUserId() << "|"
            << user.getEmail() << "|"
            << user.getUsername() << "|"
            << user.getPassword() << "|"
            << user.getPhone() << "|"
            << user.getRole()->getRoleName() << endl;

    outFile.close();
    cout << "Register successful" << endl;
}

void UserRepository::updateUser(const User& updatedUser) {
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't open file to read and write" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string userId, email, username, password, phone, roleName;

        getline(ss, userId, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName);

        if (atoi(userId.c_str()) == updatedUser.getUserId()) {
            tempFile << updatedUser.getUserId() << "|"
                     << updatedUser.getEmail() << "|"
                     << updatedUser.getUsername() << "|"
                     << updatedUser.getPassword() << "|"
                     << updatedUser.getPhone() << "|"
                     << updatedUser.getRole()->getRoleName() << endl;
            found = true;
        } else {
            tempFile << userId << "|"
                     << email << "|"
                     << username << "|"
                     << password << "|"
                     << phone << "|"
                     << roleName << endl;
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_userFileName);
        rename(_userTempFileName, _userFileName);
        cout << "Updated user successful" << endl;
    } else {
        remove(_userTempFileName);
        cout << "User not found" << endl;
    }
}

void UserRepository::deleteUser(int userId) {
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't open file to read and write" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, email, username, password, phone, roleName;

        getline(ss, id, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName, '|');

        if (atoi(id.c_str()) == userId) {
            found = true;  
        } else {
            tempFile << id << "|"
                     << email << "|"
                     << username << "|"
                     << password << "|"
                     << phone << "|"
                     << roleName << endl;
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_userFileName);
        rename(_userTempFileName, _userFileName);
        cout << "Deleted user successful" << endl;
    } else {
        remove(_userTempFileName);
        cout << "User not found" << endl;
    }
}

User UserRepository::getUserById(int userId) {
    ifstream inFile(_userFileName);
    if (!inFile.is_open()) {
        cerr << "Can't open file to read" << endl;
        return User();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, email, username, password, phone, roleName;

        getline(ss, id, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName, '|');

        if (atoi(id.c_str()) == userId) {
            Role* role = nullptr;
            if (roleName == "Admin") {
                role = new Admin();
            } else if (roleName == "Librarian") {
                role = new Librarian();
            } else {
                role = new Member();
            }
            inFile.close();
            return User(atoi(id.c_str()), email, username, password, phone, role);
        }
    }
    inFile.close();
    cout << "UserId not found" << endl;
    return User();
}

List<User> UserRepository::getAllUsers() {
    ifstream inFile(_userFileName);
    List<User> userList;
    if (!inFile.is_open()) {
        cerr << "Can't open file to read" << endl;
        return userList;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, email, username, password, phone, roleName;

        getline(ss, id, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName, '|');

        Role* role = nullptr;
        if (roleName == "Admin") {
            role = new Admin();
        } else if (roleName == "Librarian") {
            role = new Librarian();
        } else {
            role = new Member();
        }
        userList.InsertLast(User(atoi(id.c_str()), email, username, password, phone, role));
    }
    inFile.close();
    return userList;
}
