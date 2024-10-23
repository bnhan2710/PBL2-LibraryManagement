#include <iostream>
#include <fstream>  
#include "UserService.h"
// #include "../utils/List.h"
UserService* UserService::_userService = 0;

UserService::UserService() {
    this->_userRepository = UserRepository::initUserRepository();
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

void UserService::registerAccount(User user) {
    this->_userRepository->addUser(user);
}


void UserService::updateUser(User updatedUser) {
    this->_userRepository->updateUser(updatedUser);
}

void UserService::deleteUser(int userId){
    this->_userRepository->deleteUser(userId);
}


User UserService::getUserById(int userId) {
    return this->_userRepository->getUserById(userId);
}

