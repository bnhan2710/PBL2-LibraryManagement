#include <iostream>
#include "./User/UserService.h"
#include "./User/User.h"
using namespace std;
int main(){
    UserService* userService = UserService::initUserService();
    int id;
    string email, username, password, phone;
    // Role role;

    cout << "Nhập ID người dùng: ";
    cin >> id;
    cin.ignore();  

    cout << "Nhập email: ";
    getline(cin, email);

    cout << "Nhập tên đăng nhập: ";
    getline(cin, username);

    cout << "Nhập mật khẩu: ";
    getline(cin, password);

    cout << "Nhập số điện thoại: ";
    getline(cin, phone);


    User newUser(id, email, username, password, phone);

    userService->registerAccount(newUser);
}
