#include "UserRepository.h"
#include "../Role/Member.h"
#include "../Role/Admin.h"
#include "../Role/Librarian.h"
#include <sstream>

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
        cerr << "Error: Cannot open file for writing." << endl;
        return;
    }

    outFile << user.getUserId() << "|"
            << user.getEmail() << "|"
            << user.getUsername() << "|"
            << user.getPassword() << "|"
            << user.getPhone() << "|"
            << user.getRole()->getRoleName() << endl;

    outFile.close();
    cout << "User added successfully." << endl;
}

void UserRepository::updateUser(const User& updatedUser) {
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error: Cannot open file for reading or writing." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string userIdStr, email, username, password, phone, roleName;

        getline(ss, userIdStr, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName);

        int userId = stoi(userIdStr);
        if (userId == updatedUser.getUserId()) {
            tempFile << updatedUser.getUserId() << "|"
                     << updatedUser.getEmail() << "|"
                     << updatedUser.getUsername() << "|"
                     << updatedUser.getPassword() << "|"
                     << updatedUser.getPhone() << "|"
                     << updatedUser.getRole()->getRoleName() << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_userFileName);
        rename(_userTempFileName, _userFileName);
        cout << "User updated successfully." << endl;
    } else {
        remove(_userTempFileName);
        cerr << "Error: User not found." << endl;
    }
}

void UserRepository::deleteUser(int userId) {
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error: Cannot open file for reading or writing." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string userIdStr;
        getline(ss, userIdStr, '|');
        int id = stoi(userIdStr);

        if (id != userId) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(_userFileName);
        rename(_userTempFileName, _userFileName);
        cout << "User deleted successfully." << endl;
    } else {
        remove(_userTempFileName);
        cerr << "Error: User not found." << endl;
    }
}

User UserRepository::getUserById(int userId) {
    ifstream inFile(_userFileName);
    if (!inFile.is_open()) {
        cerr << "Error: Cannot open file for reading." << endl;
        return User();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string userIdStr, email, username, password, phone, roleName;

        getline(ss, userIdStr, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName);

        int id = stoi(userIdStr);
        if (id == userId) {
            Role* role = nullptr;
            if (roleName == "Admin") {
                role = new Admin();
            } else if (roleName == "Librarian") {
                role = new Librarian();
            } else {
                role = new Member();
            }

            inFile.close();
            return User(id, email, username, password, phone, role);
        }
    }

    inFile.close();
    cerr << "Error: User not found." << endl;
    return User();
}

List<User> UserRepository::getAllUsers() {
    ifstream inFile(_userFileName);
    List<User> userList;
    if (!inFile.is_open()) {
        cerr << "Error: Cannot open file for reading." << endl;
        return userList;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string userIdStr, email, username, password, phone, roleName;

        getline(ss, userIdStr, '|');
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, roleName);

        int id = stoi(userIdStr);
        Role* role = nullptr;
        if (roleName == "Admin") {
            role = new Admin();
        } else if (roleName == "Librarian") {
            role = new Librarian();
        } else {
            role = new Member();
        }

        User user(id, email, username, password, phone, role);
        userList.InsertLast(user);
    }

    inFile.close();
    return userList;
}
