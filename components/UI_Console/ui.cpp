// #include <iostream>
// using namespace std;

// class UI {
//     private:
//     void Separator() {
//         cout << "=====================================\n";
//     }

//     public:


//     void MainMenu() {
//         Separator();
//         cout << "             MAIN MENU               \n";
//         Separator();
//         cout << "  1. User\n";
//         cout << "  2. Category\n";
//         cout << "  3. Publisher\n";
//         cout << "  4. Book\n";
//         cout << "  5. Author\n";
//         cout << "  6. Exit\n";
//         Separator();
//         cout << endl;
//     }

//     void UserMenu() {
//         Separator();
//         cout << "             USER MENU               \n";
//         Separator();
//         cout << "  1. Add\n";
//         cout << "  2. Update\n";
//         cout << "  3. Delete\n";
//         cout << "  4. Show\n";
//         cout << "  5. Exit\n";
//         Separator();
//         cout << endl;
//     }

//     void CategoryMenu() {
//         Separator();
//         cout << "           CATEGORY MENU             \n";
//         Separator();
//         cout << "  1. Add\n";
//         cout << "  2. Update\n";
//         cout << "  3. Delete\n";
//         cout << "  4. Show\n";
//         cout << "  5. Exit\n";
//         Separator();
//         cout << endl;
//     }

//     void PublisherMenu() {
//         Separator();
//         cout << "           PUBLISHER MENU            \n";
//         Separator();
//         cout << "  1. Add\n";
//         cout << "  2. Update\n";
//         cout << "  3. Delete\n";
//         cout << "  4. Show\n";
//         cout << "  5. Exit\n";
//         Separator();
//         cout << endl;
//     }

//     void BookMenu() {
//         Separator();
//         cout << "             BOOK MENU               \n";
//         Separator();
//         cout << "  1. Add\n";
//         cout << "  2. Update\n";
//         cout << "  3. Delete\n";
//         cout << "  4. Show\n";
//         cout << "  5. Exit\n";
//         Separator();
//         cout << endl;
//     }

//     void AuthorMenu() {
//         Separator();
//         cout << "            AUTHOR MENU              \n";
//         Separator();
//         cout << "  1. Add\n";
//         cout << "  2. Update\n";
//         cout << "  3. Delete\n";
//         cout << "  4. Show\n";
//         cout << "  5. Exit\n";
//         Separator();
//         cout << endl;
//     }

//     void LoginMenu() {
//         Separator();
//         cout << "             LOGIN MENU              \n";
//         Separator();
//         cout << "  1. Login\n";
//         cout << "  2. Register\n";
//         cout << "  3. Exit\n";
//         Separator();
//         cout << endl;
//     }
// };
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "raygui.h"
#include <cstring>
#include <string>
#include <cmath>
#include "../User/User.h"
#include "../../utils/List.h"
#include "../User/UserService.h"
#include "../Category/Category.h"
#include "../Category/CategoryService.h"
#include "../Publisher/Publisher.h"
#include "../Publisher/PublisherService.h"
#include "../../src/auth/auth.h"
using namespace std;
// Dữ liệu mẫu
static const int windowWidth = 1280;
static const int windowHeight = 880;
static const int loginWidth = 600;
static const int loginHeight = 500;
Font textFont, titleFont;

enum State {
    Menu,
    User,
    Category,
    Publisher,
    Book,
    BorrowReturn,
    Author,
    Exit
};

class UI {
    private:
        char* text = new char[64];
        bool editMode = false; 
        bool onAddOpen = false;
        bool onEditOpen = false;
        int rowSelected = -1;
        int idSelected = -1;
        const int userRenderDefault = 20;
        int scrollPosition = 0;
        int scrollRenderTable = 0;
        Rectangle tableBounds = { 100, 150, 1100, (float)(30 + userRenderDefault * 30 )};
        Rectangle scrollMove = { tableBounds.x + tableBounds.width - 30, tableBounds.y + 30, 30, tableBounds.height - 30 };
        Rectangle functionBarBounds = { 0, 0, 300, windowHeight };
        Rectangle textBoxBounds = { tableBounds.x + 150, tableBounds.y - 50, 400, 40 };
        Rectangle addBtnBounds = { tableBounds.x + 590, tableBounds.y - 50, 150, 40 };
        Rectangle editBtnBounds = { tableBounds.x + 770, tableBounds.y - 50, 150, 40 };
        Rectangle deleteBtnBounds = { tableBounds.x + 950, tableBounds.y - 50, 150, 40 };
        Rectangle textDivBounds = { tableBounds.x + 140, tableBounds.y, 800, 600 };
        Rectangle closeDivBounds = { textDivBounds.x + textDivBounds.width - 80, textDivBounds.y + 20, 50, 40 };
    public:
        void DrawUserTable( UserService* userService, float wheelMove,Vector2 mousePos, string searchBar = "search user") 
        {
            List<class User> userList = userService->getUser();
            int userCount = userList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( userCount / ( userRenderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
            DrawTextEx(titleFont, "User List", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox(textBoxBounds, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), textBoxBounds)) {
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                    } else {
                        searchBar = string(text);
                    }
                }
            }
            if( GuiButton(addBtnBounds, "Add new User") ) {
                char *_username = new char[32];
                char *_email = new char[32];
                char *_phone = new char[32];
                char *_password = new char[32];
                bool userEdit = false;
                bool emailEdit = false;
                bool phoneEdit = false;
                bool passwordEdit = false;
                _username = strcpy(_username, "");
                _email = strcpy(_email, "");
                _phone = strcpy(_phone, "");
                _password = strcpy(_password, "");
                while (!onAddOpen)
                {
                    BeginDrawing();
                    ClearBackground(GRAY);
                    DrawRectangleRec(textDivBounds, WHITE);
                    if( GuiButton(closeDivBounds, "X") ) {
                        onAddOpen = !onAddOpen;
                    }
                    DrawTextEx(titleFont, "Add new User", Vector2{textDivBounds.x + 300, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                    GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 150, 250, 40 }, "Username");
                    if (GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 150, 450, 40 }, _username, 64, userEdit)) {
                        _username = strcpy(_username, _username);
                        userEdit = !userEdit;
                    }
                    GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 230, 250, 40 }, "Email");
                    if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 230, 450, 40 }, _email, 64, emailEdit) ) {
                        _email = strcpy(_email, _email);
                        emailEdit = !emailEdit;
                    }
                    if ( GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 310, 250, 40 }, "Phone") ) {
                        _phone = strcpy(_phone, _phone);
                        phoneEdit = !phoneEdit;
                    }
                    if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 310, 450, 40 }, _phone, 64, phoneEdit) ) {
                        _phone = strcpy(_phone, _phone);
                        phoneEdit = !phoneEdit;
                    }
                    GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 390, 250, 40 }, "Password");
                    if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 390, 450, 40 }, _password, 64, passwordEdit) ) {
                        _password = strcpy(_password, _password);
                        passwordEdit = !passwordEdit;
                    }                    
                    if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Add") ) {
                        string username = string(_username);
                        string email = string(_email);
                        string phone = string(_phone);
                        string password = string(_password);
                        userService->createUser(username, email, phone, password);
                        onAddOpen = !onAddOpen;
                    }
                    EndDrawing();
                }
            }
            onAddOpen = false;
            if ( GuiButton(editBtnBounds, "Edit") && idSelected > 0 ) {
                char *_username = new char[32];
                char *_email = new char[32];
                char *_phone = new char[32];
                char *_password = new char[32];
                bool userEdit = false;
                bool emailEdit = false;
                bool phoneEdit = false;
                bool passwordEdit = false;
                _username = strcpy(_username, userList[idSelected - 1].getUsername().c_str());
                _email = strcpy(_email, userList[idSelected - 1].getEmail().c_str());
                _phone = strcpy(_phone, userList[idSelected - 1].getPhone().c_str());
                _password = strcpy(_password, userList[idSelected - 1].getPassword().c_str());
                while (!onEditOpen)
                {
                    BeginDrawing();
                    ClearBackground(GRAY);
                    DrawRectangleRec(textDivBounds, WHITE);
                    if( GuiButton(closeDivBounds, "X") ) {
                        onEditOpen = !onEditOpen;
                    }
                    DrawTextEx(titleFont, "Edit User", Vector2{textDivBounds.x + 300, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                    GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 150, 250, 40 }, "Username");
                    if (GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 150, 450, 40 }, _username, 64, userEdit)) {
                        _username = strcpy(_username, _username);
                        userEdit = !userEdit;
                    }
                    GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 230, 250, 40 }, "Email");
                    if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 230, 450, 40 }, _email, 64, emailEdit) ) {
                        _email = strcpy(_email, _email);
                        emailEdit = !emailEdit;
                    }
                    if ( GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 310, 250, 40 }, "Phone") ) {
                        _phone = strcpy(_phone, _phone);
                        phoneEdit = !phoneEdit;
                    }
                    if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 310, 450, 40 }, _phone, 64, phoneEdit) ) {
                        _phone = strcpy(_phone, _phone);
                        phoneEdit = !phoneEdit;
                    }
                    GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 390, 250, 40 }, "Password");
                    if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 390, 450, 40 }, _password, 64, passwordEdit) ) {
                        _password = strcpy(_password, _password);
                        passwordEdit = !passwordEdit;
                    }                    
                    if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Save") ) {
                        string username = string(_username);
                        string email = string(_email);
                        string phone = string(_phone);
                        string password = string(_password);
                        userService->updateUser(idSelected, username, email, phone, password);
                        onEditOpen = !onEditOpen;
                        idSelected = -1;
                        rowSelected = -1;
                    }
                    EndDrawing();
                }
            }
            onEditOpen = false;
            GuiButton(deleteBtnBounds, "Delete");
            int cnt = 0;
            DrawRectangleRec(tableBounds, LIGHTGRAY);
            DrawTextEx(textFont, "STT", Vector2{tableBounds.x + 10, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Name", Vector2{tableBounds.x + 100, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Email", Vector2{tableBounds.x + 300, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Phone", Vector2{tableBounds.x + 600, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Password", Vector2{tableBounds.x + 800, tableBounds.y + 10}, 20, 2, DARKGRAY);

            if (wheelMove != 0.0 && wheelMove > 0 ||
                (CheckCollisionPointRec(mousePos, scrollBounds) &&
                IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseDelta().y < 0)) {
                scrollRenderTable += -1;
                if (cnt > 0) {
                cnt--;
                }
            }
            if (wheelMove != 0.0 && wheelMove < 0 ||
                (CheckCollisionPointRec(mousePos, scrollBounds) &&
                IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseDelta().y > 0)) {
                scrollRenderTable += 1;
                if (cnt > 0) {
                cnt--;
                }
            }
            if (scrollRenderTable >= userCount - userRenderDefault + 1) {
                scrollRenderTable += -1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable += 1;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < userRenderDefault + scrollRenderTable && i < userCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width, 30};
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mousePos, rowBounds)) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        } else {
                            idSelected = userList[i].getUserId();
                            rowSelected = i;
                        }
                    } else if ( !CheckCollisionPointRec(mousePos, editBtnBounds) && !CheckCollisionPointRec(mousePos, deleteBtnBounds) ) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        }
                    }
                }
                if ( rowSelected != i ) {
                    DrawRectangleRec(rowBounds, WHITE);
                } else {
                    DrawRectangleRec(rowBounds, GREEN);
                }
                DrawTextEx(textFont, TextFormat("%d", userList[i].getUserId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getUsername().c_str(),
                        Vector2{rowBounds.x + 100, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getEmail().c_str(),
                        Vector2{
                            rowBounds.x + 300,
                            rowBounds.y + 5,
                        },
                        20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getPhone().c_str(),
                        Vector2{rowBounds.x + 600, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getPassword().c_str(),
                        Vector2{rowBounds.x + 800, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }
            DrawRectangleRec(scrollMove, GRAY);
            int move = (int)((scrollMove.height - scrollHeight) /
                            (userCount - userRenderDefault));
            int distMouseWithScroll = (mousePos.y - scrollMove.y);
            if (wheelMove != 0.0 && wheelMove > 0 ||
                (CheckCollisionPointRec(mousePos, scrollBounds) &&
                IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseDelta().y < 0)) {
                scrollPosition += 1 * move;
            }
            if (wheelMove != 0.0 && wheelMove < 0 ||
                (CheckCollisionPointRec(mousePos, scrollBounds) &&
                IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseDelta().y > 0)) {
                scrollPosition += -1 * move;
            }
            float currentScrollY = (scrollMove.y - scrollPosition);
            if (currentScrollY < scrollMove.y) {
                scrollPosition -= 1 * move;
                currentScrollY = scrollMove.y;
            }
            if (currentScrollY > fabs(scrollMove.y + scrollMove.height - scrollHeight)) {
                scrollPosition -= -1 * move;
                currentScrollY = fabs(scrollMove.y + scrollMove.height - scrollHeight);
            }
            scrollBounds.y = currentScrollY;
            DrawRectangleRec(scrollBounds, BLACK);
        }

        void LoadText() {
            textFont = LoadFontEx("components/UI_Console/font/times.ttf", 20, 0, 0);
            titleFont = LoadFontEx("components/UI_Console/font/times.ttf", 40, 0, 0);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
            GuiSetFont(textFont);
        }

        void InitApplication() {
            InitWindow(windowWidth, windowHeight, "Library Management");
            SetTargetFPS(60);
        }

        void InitLogin() {
            InitWindow(loginWidth, loginHeight, "Library Management Login");
            SetTargetFPS(60);
        }

        bool DrawLoginForm() {
            char* username = new char[64];
            char* password = new char[64];
            bool userEdit = false;
            bool passwordEdit = false;
            username = strcpy(username, "");
            password = strcpy(password, "");
            Auth auth;
            bool onLogin = false;
            InitLogin();
            LoadText();
            while (!WindowShouldClose() && !onLogin)
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTextEx(titleFont, "Login", Vector2{ ( loginWidth / 2 ) - 50, 80 }, 36, 2, DARKGRAY);
                GuiLabel(Rectangle{ 50, 200, 250, 40 }, "Username");
                if (GuiTextBox(Rectangle{ 150, 200, 350, 40 }, username, 64, userEdit)) {
                    username = strcpy(username, username);
                    userEdit = !userEdit;
                }
                GuiLabel(Rectangle{ 50, 300, 250, 40 }, "Password");
                if ( GuiTextBox(Rectangle{ 150, 300, 350, 40 }, password, 64, passwordEdit) ) {
                    password = strcpy(password, password);
                    passwordEdit = !passwordEdit;
                }
                if( GuiButton(Rectangle{ ( loginWidth / 2 ) - 50, 400, 100, 40 }, "Login") ) {
                    string _username = string(username);
                    string _password = string(password);
                    if ( auth.login( _username, _password ) ) {
                        onLogin = !onLogin;
                        return onLogin;
                    }
                }
                EndDrawing();
            }
            return onLogin;
        }

        State DrawBackButton(State currentState) {
            if (GuiButton(Rectangle{tableBounds.x + 1000, tableBounds.y - 120, 100, 50}, GuiIconText(ICON_ARROW_LEFT, "Back"))) {
                return State::Menu;
            }
            return currentState;
        }

        State DrawFunctionBar() {
            DrawTextEx(titleFont, "MENU", Vector2{ ( windowWidth / 2 ) - 50, 150 }, 40, 2, DARKGRAY);
            if (GuiButton(Rectangle{(int)(windowWidth / 2) - 400, 300, 200, 75}, "User")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search user");
                return State::User;
            }
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 300, 200, 75 }, "Category");
            GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 300, 200, 75 }, "Publisher");
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 400, 450, 200, 75 }, "Book");
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Borrow Return");
            GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 450, 200, 75 }, "Author");
            if( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 600, 200, 75 }, "Exit") ) { 
                return State::Exit;
            }
            return State::Menu;
        }

        void End() {
            onAddOpen = false;
            onEditOpen = false;
            UnloadFont(textFont);
            UnloadFont(titleFont);
        }
};
