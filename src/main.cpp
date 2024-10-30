#include <iostream>
#include "./User/UserService.h"
#include "./User/User.h"
#include "./Category/Category.h"
#include "./Category/CategoryService.h"
#include "./Publisher/Publisher.h"
#include "./Publisher/PublisherService.h"
#include "./UI_Console/ui.cpp"
using namespace std;

void handleUserMenu(UI& ui, UserService* userService) {
    int userChoice;
    do {
        ui.UserMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;
        // Handle user 
        switch( userChoice ) {
            case 1:
                cout << "Create new user\n";
                userService->createUser();
                break;
            case 2:
                cout << "Updating user\n";
                userService->updateUser();
                break;
            case 3:
                cout << "Deleting user\n";
                userService->deleteUser();
                break;
            case 4:
                cout << "Getting user by ID\n";
                userService->getUserById();
                break;
            case 5:
                cout << "Exiting user menu\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (userChoice != 5);
}

void handleCategoryMenu(UI& ui, CategoryService* categoryService) {
    int categoryChoice;
    do {
        ui.CategoryMenu();
        cout << "Enter your choice: ";
        cin >> categoryChoice;
        // Handle category 
        if (categoryChoice != 5) {
            cout << "Selected Category option " << categoryChoice << "\n";
        }
    } while (categoryChoice != 5);
}

void handlePublisherMenu(UI& ui, PublisherService* publisherService) {
    int publisherChoice;
    do {
        ui.PublisherMenu();
        cout << "Enter your choice: ";
        cin >> publisherChoice;
        // Handle publisher 
        if (publisherChoice != 5) {
            cout << "Selected Publisher option " << publisherChoice << "\n";
        }
    } while (publisherChoice != 5);
}

void handleBookMenu(UI& ui) {
    int bookChoice;
    do {
        ui.BookMenu();
        cout << "Enter your choice: ";
        cin >> bookChoice;
        // Handle book 
        if (bookChoice != 5) {
            cout << "Selected Book option " << bookChoice << "\n";
        }
    } while (bookChoice != 5);
}

void handleAuthorMenu(UI& ui) {
    int authorChoice;
    do {
        ui.AuthorMenu();
        cout << "Enter your choice: ";
        cin >> authorChoice;
        // Handle author 
        if (authorChoice != 5) {
            cout << "Selected Author option " << authorChoice << "\n";
        }
    } while (authorChoice != 5);
}

int main() {
    UI ui;
    UserService* userService = UserService::initUserService();
    CategoryService* categoryService = CategoryService::initCategoryService();
    PublisherService* publisherService = PublisherService::initPublisherService();
    int choice;

    do {
        ui.MainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                handleUserMenu(ui, userService);
                break;
            case 2:
                handleCategoryMenu(ui, categoryService);
                break;
            case 3:
                handlePublisherMenu(ui, publisherService);
                break;
            case 4:
                handleBookMenu(ui);
                break;
            case 5: 
                handleAuthorMenu(ui);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
