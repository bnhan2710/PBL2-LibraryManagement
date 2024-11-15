// #include <iostream>
// #include "./User/UserService.h"
// #include "./User/User.h"
// #include "./Category/Category.h"
// #include "./Category/CategoryService.h"
// #include "./Publisher/Publisher.h"
// #include "./Publisher/PublisherService.h"
// #include "../src/auth/auth.h"
// #include "./UI_Console/ui.cpp"
// using namespace std;

// bool handleLogin(UI& ui, Auth* auth) {
//     string username, password;
//     cout << "Enter username: ";
//     cin >> username;
//     cout << "Enter password: ";
//     cin >> password;
//     if (auth->login(username, password)) {
//         cout << "Login successful\n";
//         return true;
//     } else {
//         cout << "Login failed\n";
//         return false;
//     }
// }

// void handleUserMenu(UI& ui, UserService* userService) {
//     int userChoice;
//     do {
//         ui.UserMenu();
//         cout << "Enter your choice: ";
//         cin >> userChoice;
//         // Handle user 
//         switch( userChoice ) {
//             case 1:
//                 cout << "Create new user\n";
//                 userService->createUser();
//                 break;
//             case 2:
//                 cout << "Updating user\n";
//                 userService->updateUser();
//                 break;
//             case 3:
//                 cout << "Deleting user\n";
//                 userService->deleteUser();
//                 break;
//             case 4:
//                 cout << "Getting user\n";
//                 userService->getUser();
//                 break;
//             case 5:
//                 cout << "Exiting user menu\n";
//                 break;
//             default:
//                 cout << "Invalid choice, please try again.\n";
//         }
//     } while (userChoice != 5);
// }

// void handleCategoryMenu(UI& ui, CategoryService* categoryService) {
//     int categoryChoice;
//     do {
//         ui.CategoryMenu();
//         cout << "Enter your choice: ";
//         cin >> categoryChoice;
//         // Handle category 
//         switch( categoryChoice ) {
//             case 1:
//                 cout << "create new Category\n";
//                 categoryService->addCategory();
//                 break;
//             case 2:
//                 cout << "Updating Category\n";
//                 categoryService->updateCategory();
//                 break;
//             case 3:
//                 cout << "Deleting Category\n";
//                 categoryService->deleteCategory();
//                 break;
//             case 4:
//                 cout << "Getting Category\n";
//                 categoryService->getCategory();
//                 break;
//             case 5:
//                 cout << "Exiting user menu\n";
//                 break;
//             default:
//                 cout << "Invalid choice, please try again.\n";
//         }        
//     } while (categoryChoice != 5);
// }

// void handlePublisherMenu(UI& ui, PublisherService* publisherService) {
//     int publisherChoice;
//     do {
//         ui.PublisherMenu();
//         cout << "Enter your choice: ";
//         cin >> publisherChoice;
//         // Handle publisher 
//         switch( publisherChoice ) {
//             case 1:
//                 cout << "create new Publisher\n";
//                 publisherService->addPublisher();
//                 break;
//             case 2:
//                 cout << "Updating Publisher\n";
//                 publisherService->updatePublisher();
//                 break;
//             case 3:
//                 cout << "Deleting Publisher\n";
//                 publisherService->deletePublisher();
//                 break;
//             case 4:
//                 cout << "Getting Publisher\n";
//                 publisherService->getPublisher();
//                 break;
//             case 5:
//                 cout << "Exiting user menu\n";
//                 break;
//             default:
//                 cout << "Invalid choice, please try again.\n";
//         }
//     } while (publisherChoice != 5);
// }

// void handleBookMenu(UI& ui) {
//     int bookChoice;
//     do {
//         ui.BookMenu();
//         cout << "Enter your choice: ";
//         cin >> bookChoice;
//         // Handle book 
//         if (bookChoice != 5) {
//             cout << "Selected Book option " << bookChoice << "\n";
//         }
//     } while (bookChoice != 5);
// }

// void handleAuthorMenu(UI& ui) {
//     int authorChoice;
//     do {
//         ui.AuthorMenu();
//         cout << "Enter your choice: ";
//         cin >> authorChoice;
//         // Handle author 
//         if (authorChoice != 5) {
//             cout << "Selected Author option " << authorChoice << "\n";
//         }
//     } while (authorChoice != 5);
// }

// int main() {
//     UI ui;
//     List<User> users;
//     UserService* userService = UserService::initUserService();
//     CategoryService* categoryService = CategoryService::initCategoryService();
//     PublisherService* publisherService = PublisherService::initPublisherService();
//     Auth* auth = new Auth();
//     if(!handleLogin(ui, auth)) {
//         return 0;
//     }
//     int choice;
//     do {
//         ui.MainMenu();
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 handleUserMenu(ui, userService);
//                 break;
//             case 2:
//                 handleCategoryMenu(ui, categoryService);
//                 break;
//             case 3:
//                 handlePublisherMenu(ui, publisherService);
//                 break;
//             case 4:
//                 handleBookMenu(ui);
//                 break;
//             case 5: 
//                 handleAuthorMenu(ui);
//                 break;
//             case 6:
//                 cout << "Exiting...\n";
//                 break;
//             default:
//                 cout << "Invalid choice, please try again.\n";
//         }
//     } while (choice != 5);

//     return 0;
// }
#include "./UI_Console/ui.cpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int main(void)
{
    UI ui;
    UserService* userService = UserService::initUserService();
    ui.DrawLoginForm();
    /* if ( !ui.DrawLoginForm() ) { */
    /*     return 0; */
    /* } */
    ui.InitApplication();
    ui.LoadText();
    State currentState = State::Menu;
    while (!WindowShouldClose() && currentState != State::Exit )
    {
        float wheelMove = GetMouseWheelMove();
        Vector2 mousePos = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currentState) {
            case State::Menu: {
                currentState = ui.DrawFunctionBar();
                break;
            }
            case State::User: {
                ui.DrawUserTable( userService, wheelMove, mousePos);
                currentState = ui.DrawBackButton(currentState);
                break;
            }
            case State::Category: {
                break;
            }
            case State::Publisher: {
                break;
            }
            case State::Book: {
                break;
            }
            case State::BorrowReturn: {
                break;
            }
            case State::Author: {
                break;
            }
            case State::Exit: {
                break;
            }
        }
        EndDrawing();
    }
    ui.End();
    CloseWindow();
    return 0;
}
