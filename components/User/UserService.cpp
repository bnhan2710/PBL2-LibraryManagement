#include <iostream>
#include <fstream>  
#include "UserService.h"
using namespace std;
UserService* UserService::_userService = 0;
string email, username, password, phone;
int userId;

UserService::UserService() {
    this->_userRepository = UserRepository::initUserRepository();
    UserService::_userList = this->_userRepository->getAllUsers();
}

UserService* UserService::initUserService() {
    if (_userService == 0) {
        _userService = new UserService();
    }
    return _userService;
}

UserService::~UserService() {
    delete _userService;
}

void UserService::createUser() {
    userId = _userList.GetLength() + 1;
    cin.ignore();
    cout << "Enter email: ";
    cin >> email;
    cin.ignore();
    cout << "Enter username: ";
    cin >> username;
    cin.ignore();
    cout << "Enter password: ";
    cin >> password;
    cin.ignore();
    cout << "Enter phone: ";
    cin >> phone;
    cin.ignore();
    User user(userId, email, username, password, phone);
    this->_userList.InsertLast(user);
    this->_userRepository->addUser(user);
}


void UserService::updateUser() {
    cout << "Enter user ID: ";
    cin >> userId;
    cin.ignore();
    User isExistedUser = this->_userRepository->getUserById(userId); 
    if (isExistedUser.getUserId() == 0) {
        return;
    }
    int userChoice;
    do {
        cout << "=====================================\n";
        cout << "1. Update email" << endl;
        cout << "2. Update username" << endl;
        cout << "3. Update password" << endl;
        cout << "4. Update phone" << endl;
        cout << "5. Exit" << endl;
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
            case 1:
                cout << "Enter new email: ";
                cin >> email;
                cin.ignore();
                isExistedUser.setEmail(email);
                break;
            case 2:
                cout << "Enter new username: ";
                cin >> username;
                cin.ignore();
                isExistedUser.setUsername(username);
                break;
            case 3:
                cout << "Enter new password: ";
                cin >> password;
                cin.ignore();
                isExistedUser.setPassword(password);
                break;
            case 4:
                cout << "Enter new phone: ";
                cin >> phone;
                cin.ignore();
                isExistedUser.setPhone(phone);
                break;
            case 5: 
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (userChoice != 5);
    this->_userRepository->updateUser(isExistedUser);
}

void UserService::deleteUser(){
    cout << "Enter user ID: ";
    cin >> userId;
    cin.ignore();
    User isExistedUser = this->_userRepository->getUserById(userId);
    if (isExistedUser.getUserId() == 0) {
        return;
    }
    isExistedUser.setEmail("999");
    isExistedUser.setUsername("999");
    isExistedUser.setPassword("999");
    isExistedUser.setPhone("999");
    this->_userRepository->updateUser(isExistedUser);
}


List<User> UserService::getUser( int userId ) {
    List<User> userList;
    User user = this->_userRepository->getUserById(userId);
    userList.InsertLast(user);
    return userList;
}

List<User> UserService::getUser() {
    return this->_userRepository->getAllUsers();
}
