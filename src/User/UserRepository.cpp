#include "UserRepository.h"

UserRepository* UserRepository::_userRepository = nullptr;
const char* UserRepository::_userFileName = "database/User.txt";
const char* UserRepository::_userTempFileName = "database/TempUser.txt";

UserRepository::UserRepository() {
}

UserRepository* UserRepository::initUserRepository() {
    if (_userRepository == nullptr) {
        _userRepository = new UserRepository();
    }
    return _userRepository;
}

UserRepository::~UserRepository() {
}

void UserRepository::addUser(User user) {
    ofstream outFile;
    outFile.open(_userFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    outFile << user.getUserId() << " "
            << user.getEmail() << " "
            << user.getUsername() << " "
            << user.getPassword() << " "
            << user.getPhone() << " " 
            << endl;

    outFile.close();
    cout << "Register successful" << endl;
}

void UserRepository::updateUser(User updatedUser) {
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    bool found = false;
    int userId;
    string email, username, password, phone;
    while (inFile >> userId >> email >> username >> password >> phone) {
        if (userId == updatedUser.getUserId()) {
            tempFile << updatedUser.getUserId() << " "
                     << updatedUser.getEmail() << " "
                     << updatedUser.getUsername() << " "
                     << updatedUser.getPassword() << " "
                     << updatedUser.getPhone() << " " 
                     << endl;
            found = true;
        } else {
            tempFile << userId << " "
                     << email << " "
                     << username << " "
                     << password << " "
                     << phone << " " 
                     << endl;
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

void UserRepository::deleteUser(int userId){
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr <<  "Can't not open file to read and write" << endl;
        return;
    }
    bool found = false;
    int id;
    string email, username, password, phone;
    while (inFile >> id >> email >> username >> password >> phone) {
        if (id == userId) {
            found = true;
        } else {
            tempFile << id << " "
                     << email << " "
                     << username << " "
                     << password << " "
                     << phone << " " 
                     << endl;
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
        cerr << "Can't not open file to read and write" <<  endl;
        return User();
    }
    int id;
    string email, username, password, phone;
    while (inFile >> id >> email >> username >> password >> phone) {
        if (id == userId) {
            inFile.close();
            return User(id, email, username, password, phone);
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
        cerr << "Can't not open file to read and write" << endl;
        return userList;
    }
    int id;
    string email, username, password, phone;
    while (inFile >> id >> email >> username >> password >> phone) {
        cout << id << " " << email << " " << username << " " << password << " " << phone << endl;
    }
    inFile.close();
    return userList;
}