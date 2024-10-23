#include <iostream>
#include "./User/UserService.h"
#include "./User/User.h"
// #include "./utils/password.h"
using namespace std;
int main(){
    UserService* userService = UserService::initUserService();
    int id;
    string email, username, password, phone;

    cout << "Nhập ID người dùng: ";
    cin >> id;
    cin.ignore();  

    cout << "Nhập email: ";
    getline(cin, email);

    cout << "Nhập tên đăng nhập: ";
    getline(cin, username);

    cout << "Nhập mật khẩu: ";
    getline(cin, password);
    // string hashedPassword = PasswordUtil::hashPassword(password);
    cout << "Nhập số điện thoại: ";
    getline(cin, phone);


    User registerUser(id, email, username, password, phone);

    userService->registerAccount(registerUser);

    cout << "Nhập số điện thoại: ";
    getline(cin, phone);
    
    User UpdateUser(id, email, username, password, phone);
    userService->updateUser(UpdateUser);

    // userService->deleteUser(id);
}
