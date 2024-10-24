#include <iostream>
#include "./User/UserService.h"
#include "./User/User.h"
#include "./Category/Category.h"
#include "./Category/CategoryService.h"
#include "./Publisher/Publisher.h"
#include "./Publisher/PublisherService.h"
// #include "./utils/password.h"
using namespace std;
int main(){
    UserService* userService = UserService::initUserService();
    CategoryService* categoryService = CategoryService::initCategoryService();
    PublisherService* publisherService = PublisherService::initPublisherService();
    int id;
    string email, username, password, phone;
    int CategoryId;
    string CategoryName;
    int PublisherId;
    string PublisherName, Address, ContactInfo;

    // cout << "NID ";
    // cin >> id;
    // cin.ignore();  

    // cout << "email: ";
    // getline(cin, email);

    // cout << "username ";
    // getline(cin, username);

    // cout << "pass ";
    // getline(cin, password);
    // // string hashedPassword = PasswordUtil::hashPassword(password);
    // cout << "sdt ";
    // getline(cin, phone);


    // User registerUser(id, email, username, password, phone);

    // userService->registerAccount(registerUser);

    // cout << "Nhap sdt: ";
    // getline(cin, phone);
    
    // User UpdateUser(id, email, username, password, phone);
    // userService->updateUser(UpdateUser);

    // cout << "Nhap CategoryId : ";
    // cin >> CategoryId;
    // cin.ignore();

    // cout << "Nhap CategoryName: ";
    // getline(cin, CategoryName);

    // Category newCategory( CategoryId, CategoryName );
    // categoryService->addCategory( newCategory );

    // cout << "Nhap CategoryName: ";
    // getline(cin, CategoryName);

    // Category updateCategory( CategoryId, CategoryName );
    // categoryService->updateCategory( updateCategory );

    // categoryService->deleteCategory( CategoryId );

    // cout << "Nhap PublisherId : ";
    // cin >> PublisherId;
    // cin.ignore();

    // cout << "Nhap PublisherName: ";
    // getline(cin, PublisherName);

    // cout << "Nhap Address: ";
    // getline(cin, Address);

    // cout << "Nhap ContactInfo: ";
    // getline(cin, ContactInfo);

    // Publisher newPublisher( PublisherId, PublisherName, Address, ContactInfo );

    // publisherService->addPublisher( newPublisher );

    // cout << "Nhap PublisherName: ";
    // getline(cin, PublisherName);

    // Publisher updatePublisher( PublisherId, PublisherName, Address, ContactInfo );
    // publisherService->updatePublisher( updatePublisher );

    // publisherService->deletePublisher( PublisherId );
}
