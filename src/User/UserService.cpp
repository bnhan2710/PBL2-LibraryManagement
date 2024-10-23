#include "UserService.h";

UserService* UserService::_userService = 0;

UserService::UserService() {
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

void UserService::createUser(User user) {
    
}

void UserService::updateUser(User user) {

}


void UserService::deleteUser(int userId) {

}


User UserService::getUserById(int userId) {
    return User();
}

