#include <iostream>
#include <fstream>  
#include "UserService.h"

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

void UserService::registerAccount(User user) {
    ofstream outFile;
    outFile.open("data/User.txt", ios::app);
    if (!outFile.is_open()) {
        cerr << "Không thể mở file để ghi." << std::endl;
        return;
    }

    outFile << user.getUserId() << " "
            << user.getEmail() << " "
            << user.getUsername() << " "
            << user.getPassword() << " "
            << user.getPhone() << " " << endl;

    outFile.close();
    cout << "Đăng kí tài khoản thành công!" << endl;
}

void UserService::updateUser(User user) {

}


void UserService::deleteUser(int userId) {

}


User UserService::getUserById(int userId) {
    return User();
}

