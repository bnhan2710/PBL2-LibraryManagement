#include "User.h";

User::User() {
    this->userId = 0;
    this->email = "";
    this->username = "";
    this->password = "";
    this->phone = "";
    this->role = Role();
}

User::User(int userId, string& email, string& username, string& password, string& phone, Role& role) {
    this->userId = userId;
    this->email = email;
    this->username = username;
    this->password = password;
    this->phone = phone;
    this->role = role;
}

void User::setUserId(int userId) {
    this->userId = userId;
}

int User::getUserId() {
    return this->userId;
}

void User::setEmail(string email) {
    this->email = email;
}

string User::getEmail() {
    return this->email;
}

void User::setUsername(string username) {
    this->username = username;
}

string User::getUsername() {
    return this->username;
}

void User::setPassword(string password) {
    this->password = password;
}

string User::getPassword() {
    return this->password;
}

void User::setPhone(string phone) {
    this->phone = phone;
}

string User::getPhone() {
    return this->phone;
}

void User::setRole(Role role) {
    this->role = role;
}

Role User::getRole() {
    return this->role;
}


