#include <iostream>
#include <fstream>  
#include "UserService.h"
using namespace std;
UserService* UserService::_userService = 0;
string email, username, password, phone;
int userId;

UserService::UserService() {
    this->_userRepository = UserRepository::initUserRepository();
    // UserService::_userList = this->_userRepository->getAllUsers();
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
    cout << "Enter user ID: ";
    cin >> userId;
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
    this->_userRepository->addUser(user);
}


void UserService::updateUser() {
    User isExistedUser = UserService::getUserById();
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
    this->_userRepository->deleteUser(userId);
}


User UserService::getUserById() {
    cout << "Enter user ID: ";
    cin >> userId;
    cin.ignore();
    return this->_userRepository->getUserById(userId);
}

