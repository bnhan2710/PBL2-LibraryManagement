#include <iostream>
#include <fstream>  
#include "UserService.h"
// #include "../utils/List.h"
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


void UserService::updateUser(User updatedUser) {
    ifstream inFile("data/User.txt");
    ofstream tempFile("data/TempUser.txt", ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << std::endl;
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
                     << updatedUser.getPhone() << " " << endl;
            found = true;
        } else {
            tempFile << userId << " "
                     << email << " "
                     << username << " "
                     << password << " "
                     << phone << " " << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove("data/User.txt"); 
        rename("data/TempUser.txt", "data/User.txt"); 
        cout << "Cập nhật người dùng thành công!" << endl;
    } else {
        remove("data/TempUser.txt"); 
        cout << "Người dùng không tồn tại!" << endl;
    }
}

void UserService::deleteUser(int userId){
    ifstream inFile("data/User.txt");
    ofstream tempFile("data/TempUser.txt", ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << std::endl;
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
                     << phone << " " << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove("data/User.txt"); 
        rename("data/TempUser.txt", "data/User.txt"); 
        cout << "Xóa người dùng thành công!" << endl;
    } else {
        remove("data/TempUser.txt"); 
        cout << "Người dùng không tồn tại!" << endl;
    }
}


User UserService::getUserById(int userId) {
    ifstream inFile("data/User.txt");

    if (!inFile.is_open()) {
        cerr << "Không thể mở file để đọc." << std::endl;
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
    cout << "Không tìm thấy người dùng với ID này!" << endl;
    return User();
}

