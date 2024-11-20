#include "User.h"
#include "../Role/Role.h"
User::User() {
    this->userId = 0;
    this->email = "";
    this->username = "";
    this->password = "";
    this->phone = "";
    this->role = nullptr;
}

User::User(int userId, const string& email, const string& username, const string& password, const string& phone, Role* role) {
    this->userId = userId;
    this->email = email;
    this->username = username;
    this->password = password;
    this->phone = phone;
    this->role = role;
}

User::~User() {
}

void User::setUserId(int userId) {
    this->userId = userId;
}

int User::getUserId() const {
    return this->userId;
}

void User::setEmail(const string& email) {
    this->email = email;
}

string User::getEmail() const {
    return this->email;
}

void User::setUsername(const string& username) {
    this->username = username;
}

string User::getUsername() const {
    return this->username;
}

void User::setPassword(const string& password) {
    this->password = password;
}

string User::getPassword() const {
    return this->password;
}

void User::setPhone(const string& phone) {
    this->phone = phone;
}

string User::getPhone() const {
    return this->phone;
}

void User::setRole(Role* role) {
    this->role = role;
}

Role* User::getRole() const {
    return this->role;
}


