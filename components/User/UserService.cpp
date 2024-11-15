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

void UserService::createUser(string email, string username, string password, string phone) {
    userId = _userList.GetLength() + 1;
    User user(userId, email, username, password, phone);
    this->_userList.InsertLast(user);
    this->_userRepository->addUser(user);
}


void UserService::updateUser(int userId, string username, string email, string phone, string password) {
    User isExistedUser = this->_userRepository->getUserById(userId); 
    if (isExistedUser.getUserId() == 0) {
        return;
    }
    isExistedUser.setEmail(email);
    isExistedUser.setUsername(username);
    isExistedUser.setPassword(password);
    isExistedUser.setPhone(phone);
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
