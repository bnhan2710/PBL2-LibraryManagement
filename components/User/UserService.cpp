#include <iostream>
#include "UserService.h"
#include "../Role/Member.h"
#include "../Role/Admin.h"
#include "../Role/Librarian.h"

using namespace std;

UserService* UserService::_userService = nullptr;

UserService::UserService() {
    this->_userRepository = UserRepository::initUserRepository();
    this->_userList = this->_userRepository->getAllUsers();
}

UserService::~UserService() {
}

UserService* UserService::initUserService() {
    if (_userService == nullptr) {
        _userService = new UserService();
    }
    return _userService;
}


void UserService::createUser(const string& username, const string& email, const string& phone, const string& password, Role* role) {
    int userId = _userList.GetLength() + 1;  
    Role* assignedRole = (role != nullptr) ? role : new Member();  

    User user(userId, email, username, password, phone, assignedRole);

    this->_userList.InsertLast(user);      
    this->_userRepository->addUser(user); 
    cout << "User created successfully! Username: " << username << endl;
}

void UserService::updateUser(const int userId, const string& username, const string& email, const string& phone, const string& password, Role* role) {
    User isExistedUser = this->_userRepository->getUserById(userId);
    if (isExistedUser.getUserId() == 0) {
        cout << "User not found!" << endl;
        return;
    }

    isExistedUser.setEmail(email);
    isExistedUser.setUsername(username);
    isExistedUser.setPassword(password);
    isExistedUser.setPhone(phone);

    if (role != nullptr) {
        isExistedUser.setRole(role);
    }

    this->_userRepository->updateUser(isExistedUser);
    cout << "User updated successfully! User ID: " << userId << endl;
}

void UserService::deleteUser(const int userId) {

    User isExistedUser = this->_userRepository->getUserById(userId);
    if (isExistedUser.getUserId() == 0) {
        cout << "User not found!" << endl;
        return;
    }

    isExistedUser.setUsername("0");
    isExistedUser.setEmail("0");
    isExistedUser.setPhone("0");
    isExistedUser.setPassword("0");
    if (isExistedUser.getRole() != nullptr) {
        isExistedUser.setRole(nullptr);
    }
    this->_userRepository->updateUser(isExistedUser);
    cout << "User deleted successfully! User ID: " << userId << endl;
}

List<User> UserService::getUser(int userId) {
    List<User> userList;
    User user = this->_userRepository->getUserById(userId);
    if (user.getUserId() != 0) {
        userList.InsertLast(user);
    } else {
        cout << "User not found!" << endl;
    }
    return userList;
}

List<User> UserService::getUser() {
    return this->_userRepository->getAllUsers();
}
