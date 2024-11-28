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
#include "../Book/Book.h"
#include "../Book/BookService.h"
#include "../Category/Category.h"
#include "../Category/CategoryService.h"
#include "../Publisher/Publisher.h"
#include "../Publisher/PublisherService.h"
#include "../../src/auth/auth.h"
#include "../Role/Member.h"
#include "../Role/Admin.h"
#include "../Role/Librarian.h"
using namespace std;

static const int windowWidth = 1400;
static const int windowHeight = 880;
static const int loginWidth = 600;
static const int loginHeight = 680;
static int roleOfUser = -1;
static Role* role = nullptr;
static List<string> permissions;
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

enum RoleOfUser {
    _Admin,
    _Librarian,
    _Member
};
class UI {
    private:
        char* text = new char[64];
        bool editMode = false; 
        bool onAddOpen = false;
        bool onEditOpen = false;
        bool onDeleteOpen = false;
        int rowSelected = -1;
        int idSelected = -1;
        const int renderDefault = 20;
        int scrollPosition = 0;
        int scrollRenderTable = 0;
        Rectangle tableBounds = { 50, 150, 1300, (float)(30 + renderDefault * 30 )};
        Rectangle scrollMove = { tableBounds.x + tableBounds.width - 30, tableBounds.y + 30, 30, tableBounds.height - 30 };
        Rectangle functionBarBounds = { 0, 0, 300, windowHeight };
        Rectangle textBoxBounds = { tableBounds.x + 150, tableBounds.y - 50, 400, 40 };
        Rectangle addBtnBounds = { tableBounds.x + 590, tableBounds.y - 50, 150, 40 };
        Rectangle editBtnBounds = { tableBounds.x + 770, tableBounds.y - 50, 150, 40 };
        Rectangle deleteBtnBounds = { tableBounds.x + 950, tableBounds.y - 50, 150, 40 };
        Rectangle textDivBounds = { tableBounds.x + 250, tableBounds.y, 800, 600 };
        Rectangle deleteTextDivBounds = { tableBounds.x + 250, tableBounds.y, 800, 350 };
        Rectangle closeDivBounds = { textDivBounds.x + textDivBounds.width - 80, textDivBounds.y + 20, 50, 40 };
    public:
        void DrawUserTable( UserService* userService, float wheelMove,Vector2 mousePos, string searchBar = "search user") 
        {
            List<class User> userList = userService->getUser();
            int userCount = userList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( userCount / ( renderDefault + 1 ) ) );
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
            for( int i = 0; i < permissions.GetLength(); i++ ) {
                if ( permissions[i] == "Manage Users" ) {
                    if( GuiButton(addBtnBounds, "Add new User") ) {
                        char *_username = new char[32];
                        char *_email = new char[32];
                        char *_phone = new char[32];
                        char *_password = new char[32];
                        const char *_role = "Member;Librarian";
                        int roleSelected = 0;
                        bool userEdit = false;
                        bool emailEdit = false;
                        bool phoneEdit = false;
                        bool passwordEdit = false;
                        bool roleEdit = false;
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
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 520, 150, 40 }, "Add") ) {
                                string username = string(_username);
                                string email = string(_email);
                                string phone = string(_phone);
                                string password = string(_password);
                                if ( roleSelected == 0 ) {
                                    userService->createUser(username, email, phone, password, new Member());
                                } else if ( roleSelected == 1 ) {
                                    userService->createUser(username, email, phone, password, new Librarian());
                                }
                                onAddOpen = !onAddOpen;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 120, 250, 40 }, "Username");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 120, 450, 40 }, _username, 64, userEdit)) {
                                _username = strcpy(_username, _username);
                                userEdit = !userEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 200, 250, 40 }, "Email");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 200, 450, 40 }, _email, 64, emailEdit) ) {
                                _email = strcpy(_email, _email);
                                emailEdit = !emailEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 280, 250, 40 }, "Phone");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 280, 450, 40 }, _phone, 64, phoneEdit) ) {
                                _phone = strcpy(_phone, _phone);
                                phoneEdit = !phoneEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 360, 250, 40 }, "Password");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 360, 450, 40 }, _password, 64, passwordEdit) ) {
                                _password = strcpy(_password, _password);
                                passwordEdit = !passwordEdit;
                            }                    
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 440, 250, 40 }, "Role");
                            if ( GuiDropdownBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 440, 450, 40 }, _role, &roleSelected, roleEdit) ) {
                                roleEdit = !roleEdit;
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
                        const char *_role = "Member;Librarian";
                        int roleSelected = 0;
                        bool userEdit = false;
                        bool emailEdit = false;
                        bool phoneEdit = false;
                        bool passwordEdit = false;
                        bool roleEdit = false;
                        _username = strcpy(_username, userList[idSelected - 1].getUsername().c_str());
                        _email = strcpy(_email, userList[idSelected - 1].getEmail().c_str());
                        _phone = strcpy(_phone, userList[idSelected - 1].getPhone().c_str());
                        _password = strcpy(_password, userList[idSelected - 1].getPassword().c_str());
                        if ( userList[idSelected - 1].getRole()->getRoleName() == "Member" ) {
                            roleSelected = 0;
                        } else if ( userList[idSelected - 1].getRole()->getRoleName() == "Librarian" ) {
                            roleSelected = 1;
                        } else {
                            roleSelected = -1;
                        }
                        while (!onEditOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onEditOpen = !onEditOpen;
                            }
                            DrawTextEx(titleFont, "Edit User", Vector2{textDivBounds.x + 350, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 520, 150, 40 }, "Save") ) {
                                string username = string(_username);
                                string email = string(_email);
                                string phone = string(_phone);
                                string password = string(_password);
                                if ( roleSelected == 0 ) {
                                    userService->updateUser(idSelected, username, email, phone, password, new Member());
                                } else if ( roleSelected == 1 ) {
                                    userService->updateUser(idSelected, username, email, phone, password, new Librarian());
                                }
                                onEditOpen = !onEditOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 120, 250, 40 }, "Username");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 120, 450, 40 }, _username, 64, userEdit)) {
                                _username = strcpy(_username, _username);
                                userEdit = !userEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 200, 250, 40 }, "Email");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 200, 450, 40 }, _email, 64, emailEdit) ) {
                                _email = strcpy(_email, _email);
                                emailEdit = !emailEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 280, 250, 40 }, "Phone");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 280, 450, 40 }, _phone, 64, phoneEdit) ) {
                                _phone = strcpy(_phone, _phone);
                                phoneEdit = !phoneEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 360, 250, 40 }, "Password");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 360, 450, 40 }, _password, 64, passwordEdit) ) {
                                _password = strcpy(_password, _password);
                                passwordEdit = !passwordEdit;
                            } 
                            if ( roleSelected != -1 ) {
                                GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 440, 250, 40 }, "Role");
                                if ( GuiDropdownBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 440, 450, 40 }, _role, &roleSelected, roleEdit) ) {
                                    roleEdit = !roleEdit;
                                }                    
                            }
                            EndDrawing();
                        }
                    }
                    onEditOpen = false;
                    if ( GuiButton(deleteBtnBounds, "Delete") && idSelected > 0 ) { 
                        while (!onDeleteOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(deleteTextDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            DrawTextEx(titleFont, "Are you sure to delete?", Vector2{textDivBounds.x + 250, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 200, textDivBounds.y + 250, 150, 40 }, "Yes") ) {
                                userService->deleteUser(idSelected);
                                onDeleteOpen = !onDeleteOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) + 100, textDivBounds.y + 250, 150, 40 }, "No") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onDeleteOpen = false;
                }
            } 
            int cnt = 0;
            DrawRectangleRec(tableBounds, LIGHTGRAY);
            DrawTextEx(textFont, "ID", Vector2{tableBounds.x + 10, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Name", Vector2{tableBounds.x + 60, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Email", Vector2{tableBounds.x + 290, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Password", Vector2{tableBounds.x + 640, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Phone", Vector2{tableBounds.x + 990, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Role", Vector2{tableBounds.x + 1150, tableBounds.y + 10}, 20, 2, DARKGRAY);

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
            if (scrollRenderTable >= userCount - renderDefault + 1) {
                scrollRenderTable = userCount - renderDefault + 1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable = 0;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < renderDefault + scrollRenderTable && i < userCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width - 30, 30};
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
                if ( userList[i].getUsername() == "0" && userList[i].getEmail() == "0" && userList[i].getPhone() == "0" && userList[i].getPassword() == "0" ) {
                    continue;
                }
                if ( rowSelected != i ) {
                    DrawRectangleRec(rowBounds, WHITE);
                } else {
                    DrawRectangleRec(rowBounds, GREEN);
                }
                DrawTextEx(textFont, TextFormat("%d", userList[i].getUserId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getUsername().c_str(),
                        Vector2{rowBounds.x + 60, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getEmail().c_str(),
                        Vector2{
                            rowBounds.x + 290,
                            rowBounds.y + 5,
                        },
                        20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getPassword().c_str(),
                        Vector2{rowBounds.x + 640, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getPhone().c_str(),
                        Vector2{rowBounds.x + 990, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userList[i].getRole()->getRoleName().c_str(),
                        Vector2{rowBounds.x + 1150, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }
            DrawRectangleRec(scrollMove, GRAY);
            const int move = (int)((scrollMove.height - scrollHeight) / (userCount - renderDefault));
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
            
        void DrawCategoryTable( CategoryService* categoryService, float wheelMove,Vector2 mousePos, string searchBar = "search category") 
        {  
            List<class Category> categoryList = categoryService->getCategory();
            int categoryCount = categoryList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( categoryCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
            DrawTextEx(titleFont, "Category", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
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
            for( int i = 0; i < permissions.GetLength(); i++ ) {
                if ( permissions[i] == "Manage Categories" ) {
                    if( GuiButton(addBtnBounds, "Add Category") ) {
                        char *_categoryName = new char[32];
                        bool categoryNameEdit = false;
                        _categoryName = strcpy(_categoryName, "");
                        while (!onAddOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onAddOpen = !onAddOpen;
                            }
                            DrawTextEx(titleFont, "Add Category", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 250, 250, 40 }, "Category Name");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 250, 450, 40 }, _categoryName, 64, categoryNameEdit)) {
                                _categoryName = strcpy(_categoryName, _categoryName);
                                categoryNameEdit = !categoryNameEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Add") ) {
                                string categoryName = string(_categoryName);
                                categoryService->addCategory(categoryName);
                                onAddOpen = !onAddOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onAddOpen = false;
                    if ( GuiButton(editBtnBounds, "Edit") && idSelected > 0 ) {
                        char *_categoryName = new char[32];
                        bool categoryNameEdit = false;
                        _categoryName = strcpy(_categoryName, categoryList[idSelected - 1].getCategoryName().c_str());
                        while (!onEditOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onEditOpen = !onEditOpen;
                            }
                            DrawTextEx(titleFont, "Edit category", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 250, 250, 40 }, "Category Name");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 250, 450, 40 }, _categoryName, 64, categoryNameEdit)) {
                                _categoryName = strcpy(_categoryName, _categoryName);
                                categoryNameEdit = !categoryNameEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Save") ) {
                                string categoryName = string(_categoryName);
                                categoryService->updateCategory(idSelected, categoryName );
                                onEditOpen = !onEditOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            EndDrawing();
                        }
                    }
                    onEditOpen = false;
                    if ( GuiButton(deleteBtnBounds, "Delete") && idSelected > 0 ) { 
                        while (!onDeleteOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(deleteTextDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            DrawTextEx(titleFont, "Are you sure to delete?", Vector2{textDivBounds.x + 250, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 200, textDivBounds.y + 250, 150, 40 }, "Yes") ) {
                                categoryService->deleteCategory(idSelected);
                                onDeleteOpen = !onDeleteOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) + 100, textDivBounds.y + 250, 150, 40 }, "No") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onDeleteOpen = false;
                }
            }
            int cnt = 0;
            DrawRectangleRec(tableBounds, LIGHTGRAY);
            DrawTextEx(textFont, "ID", Vector2{tableBounds.x + 10, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Category Name", Vector2{tableBounds.x + 200, tableBounds.y + 10}, 20, 2, DARKGRAY);

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
            if (scrollRenderTable >= categoryCount - renderDefault + 1) {
                scrollRenderTable = categoryCount - renderDefault + 1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable = 0;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < renderDefault + scrollRenderTable && i < categoryCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width - 30, 30};
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mousePos, rowBounds)) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        } else {
                            idSelected = categoryList[i].getCategoryId();
                            rowSelected = i;
                        }
                    } else if ( !CheckCollisionPointRec(mousePos, editBtnBounds) && !CheckCollisionPointRec(mousePos, deleteBtnBounds) ) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        }
                    }
                }
                if ( categoryList[i].getCategoryName() == "0" ) {
                    continue;
                }
                if ( rowSelected != i ) {
                    DrawRectangleRec(rowBounds, WHITE);
                } else {
                    DrawRectangleRec(rowBounds, GREEN);
                }
                DrawTextEx(textFont, TextFormat("%d", categoryList[i].getCategoryId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, categoryList[i].getCategoryName().c_str(),
                        Vector2{rowBounds.x + 200, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }

            DrawRectangleRec(scrollMove, GRAY);
            int move = (int)((scrollMove.height - scrollHeight) /
                            (categoryCount - renderDefault));
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

        void DrawPublisherTable( PublisherService* publisherService, float wheelMove,Vector2 mousePos, string searchBar = "search publisher") 
        {
            List<class Publisher> publisherList = publisherService->getPublisher();
            int publisherCount = publisherList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( publisherCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
            DrawTextEx(titleFont, "Publisher", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
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
            for( int i = 0; i < permissions.GetLength(); i++ ) {
                if ( permissions[i] == "Manage Publishers" ) {
                    if( GuiButton(addBtnBounds, "Add Publisher") ) {
                        char *_publisherName = new char[32];
                        char *_address = new char[32];
                        char *_contactInfo = new char[32];
                        bool publisherEdit = false;
                        bool addressEdit = false;
                        bool contactInfoEdit = false;
                        _publisherName = strcpy(_publisherName, "");
                        _address = strcpy(_address, "");
                        _contactInfo= strcpy(_contactInfo, "");
                        while (!onAddOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onAddOpen = !onAddOpen;
                            }
                            DrawTextEx(titleFont, "Add Publisher", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 150, 250, 40 }, "Publisher Name");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 150, 450, 40 }, _publisherName, 64, publisherEdit)) {
                                _publisherName = strcpy(_publisherName, _publisherName);
                                publisherEdit = !publisherEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 230, 250, 40 }, "Address");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 230, 450, 40 }, _address, 64, addressEdit) ) {
                                _address = strcpy(_address, _address);
                                addressEdit = !addressEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 310, 250, 40 }, "Contact Info");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 310, 450, 40 }, _contactInfo, 64, contactInfoEdit) ) {
                                _contactInfo = strcpy(_contactInfo, _contactInfo);
                                contactInfoEdit = !contactInfoEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Add") ) {
                                string publisherName = string(_publisherName);
                                string address = string(_address);
                                string contactInfo = string(_contactInfo);
                                publisherService->addPublisher(publisherName, address, contactInfo);
                                onAddOpen = !onAddOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onAddOpen = false;
                    if ( GuiButton(editBtnBounds, "Edit") && idSelected > 0 ) {
                        char *_publisherName = new char[32];
                        char *_address = new char[32];
                        char *_contactInfo = new char[32];
                        bool publisherEdit = false;
                        bool addressEdit = false;
                        bool contactInfoEdit = false;
                        _publisherName = strcpy(_publisherName, publisherList[idSelected - 1].getPublisherName().c_str());
                        _address = strcpy(_address, publisherList[idSelected - 1].getAddress().c_str());
                        _contactInfo = strcpy(_contactInfo, publisherList[idSelected - 1].getContactInfo().c_str());
                        while (!onEditOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onEditOpen = !onEditOpen;
                            }
                            DrawTextEx(titleFont, "Edit Publisher", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 150, 250, 40 }, "Publisher Name");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 150, 450, 40 }, _publisherName, 64, publisherEdit)) {
                                _publisherName = strcpy(_publisherName, _publisherName);
                                publisherEdit = !publisherEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 230, 250, 40 }, "Address");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 230, 450, 40 }, _address, 64, addressEdit) ) {
                                _address = strcpy(_address, _address);
                                addressEdit = !addressEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 310, 250, 40 }, "Contact Info");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 310, 450, 40 }, _contactInfo, 64, contactInfoEdit) ) {
                                _contactInfo = strcpy(_contactInfo, _contactInfo);
                                contactInfoEdit = !contactInfoEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Save") ) {
                                string publisherName = string(_publisherName);
                                string address = string(_address);
                                string contactInfo = string(_contactInfo);
                                publisherService->updatePublisher(idSelected, publisherName, address, contactInfo);
                                onEditOpen = !onEditOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            EndDrawing();
                        }
                    }
                    onEditOpen = false;
                    if ( GuiButton(deleteBtnBounds, "Delete") && idSelected > 0 ) { 
                        while (!onDeleteOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(deleteTextDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            DrawTextEx(titleFont, "Are you sure to delete?", Vector2{textDivBounds.x + 250, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 200, textDivBounds.y + 250, 150, 40 }, "Yes") ) {
                                publisherService->deletePublisher(idSelected);
                                onDeleteOpen = !onDeleteOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) + 100, textDivBounds.y + 250, 150, 40 }, "No") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onDeleteOpen = false;
                }
            }
            int cnt = 0;
            DrawRectangleRec(tableBounds, LIGHTGRAY);
            DrawTextEx(textFont, "ID", Vector2{tableBounds.x + 10, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Publisher Name", Vector2{tableBounds.x + 100, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Address", Vector2{tableBounds.x + 500, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Contact Info", Vector2{tableBounds.x + 900, tableBounds.y + 10}, 20, 2, DARKGRAY);

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
            if (scrollRenderTable >= publisherCount - renderDefault + 1) {
                scrollRenderTable = publisherCount - renderDefault + 1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable = 0;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < renderDefault + scrollRenderTable && i < publisherCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width - 30, 30};
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mousePos, rowBounds)) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        } else {
                            idSelected = publisherList[i].getPublisherId();
                            rowSelected = i;
                        }
                    } else if ( !CheckCollisionPointRec(mousePos, editBtnBounds) && !CheckCollisionPointRec(mousePos, deleteBtnBounds) ) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        }
                    }
                }
                if ( publisherList[i].getPublisherName() == "0" && publisherList[i].getAddress() == "0" && publisherList[i].getContactInfo() == "0" ) {
                    continue;
                }
                if ( rowSelected != i ) {
                    DrawRectangleRec(rowBounds, WHITE);
                } else {
                    DrawRectangleRec(rowBounds, GREEN);
                }
                DrawTextEx(textFont, TextFormat("%d", publisherList[i].getPublisherId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, publisherList[i].getPublisherName().c_str(),
                        Vector2{rowBounds.x + 100, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, publisherList[i].getAddress().c_str(),
                        Vector2{
                            rowBounds.x + 500,
                            rowBounds.y + 5,
                        },
                        20, 2, DARKGRAY);
                DrawTextEx(textFont, publisherList[i].getContactInfo().c_str(),
                        Vector2{rowBounds.x + 900, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }
                DrawRectangleRec(scrollMove, GRAY);
                int move = (int)((scrollMove.height - scrollHeight) /
                                (publisherCount - renderDefault));
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

        void DrawBookTable( BookService* bookService, float wheelMove,Vector2 mousePos, string searchBar = "search book") 
        {
            List<class Book> bookList = bookService->getBook();
            int bookCount = bookList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( bookCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
            DrawTextEx(titleFont, "Book", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
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
            for( int i = 0; i < permissions.GetLength(); i++ ) {
                if ( permissions[i] == "Manage Books" ) {
                    if( GuiButton(addBtnBounds, "Add Book") ) {
                        char *_title = new char[32];
                        char *_author = new char[32];
                        char *_publisher = new char[32];
                        char *_category = new char[32];
                        char *_quantity = new char[32];
                        char *_code = new char[32];
                        bool titleEdit = false;
                        bool authorEdit = false;
                        bool publisherEdit = false;
                        bool categoryEdit = false;
                        bool quantityEdit = false;
                        bool codeEdit = false;
                        _code = strcpy(_code, "");
                        _title = strcpy(_title, "");
                        _author = strcpy(_author, "");
                        _publisher = strcpy(_publisher, "");
                        _category = strcpy(_category, "");
                        _quantity = strcpy(_quantity, "");
                        while (!onAddOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onAddOpen = !onAddOpen;
                            }
                            DrawTextEx(titleFont, "Add new Book", Vector2{textDivBounds.x + 300, textDivBounds.y + 20}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 550, 150, 40 }, "Add") ) {
                                string title = string(_title);
                                string author = string(_author);
                                string publisher = string(_publisher);
                                string category = string(_category);
                                string code = string(_code);
                                int quantity = atoi(_quantity);
                                bookService->addBook(code, title, author, publisher, category, quantity);
                                onAddOpen = !onAddOpen;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 90, 250, 40 }, "Title");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 90, 450, 40 }, _title, 64, titleEdit)) {
                                _title = strcpy(_title, _title);
                                titleEdit = !titleEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 170, 250, 40 }, "Code");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 170, 450, 40 }, _code, 64, codeEdit) ) {
                                _code = strcpy(_code, _code);
                                codeEdit = !codeEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 250, 250, 40 }, "Author");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 250, 450, 40 }, _author, 64, authorEdit) ) {
                                _author = strcpy(_author, _author);
                                authorEdit = !authorEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 330, 250, 40 }, "Publisher");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 330, 450, 40 }, _publisher, 64, publisherEdit) ) {
                                _publisher = strcpy(_publisher, _publisher);
                                publisherEdit = !publisherEdit;
                            } 
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 410, 250, 40 }, "Category");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 410, 450, 40 }, _category, 64, categoryEdit) ) {
                                _category = strcpy(_category, _category);
                                categoryEdit = !categoryEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 490, 250, 40 }, "Quantity");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 490, 450, 40 }, _quantity, 64, quantityEdit) ) {
                                _quantity = strcpy(_quantity, _quantity);
                                quantityEdit = !quantityEdit;
                            }
                            EndDrawing();
                        }
                    }
                    onAddOpen = false;
                    if ( GuiButton(editBtnBounds, "Edit") && idSelected > 0 ) {
                        char *_title = new char[32];
                        char *_author = new char[32];
                        char *_publisher = new char[32];
                        char *_category = new char[32];
                        char *_quantity = new char[32];
                        char *_code = new char[32];
                        bool titleEdit = false;
                        bool authorEdit = false;
                        bool publisherEdit = false;
                        bool categoryEdit = false;
                        bool quantityEdit = false;
                        bool codeEdit = false;
                        _code = strcpy(_code, bookList[idSelected - 1].getCode().c_str());
                        _title = strcpy(_title, bookList[idSelected - 1].getTitle().c_str());
                        _author = strcpy(_author, bookList[idSelected - 1].getAuthor().c_str());
                        _publisher = strcpy(_publisher, bookList[idSelected - 1].getPublisher().c_str());
                        _category = strcpy(_category, bookList[idSelected - 1].getCategory().c_str());
                        _quantity = strcpy(_quantity, to_string(bookList[idSelected - 1].getQuantity()).c_str());
                        while (!onEditOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onEditOpen = !onEditOpen;
                            }
                            DrawTextEx(titleFont, "Edit Book", Vector2{textDivBounds.x + 350, textDivBounds.y + 20}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 550, 150, 40 }, "Save") ) {
                                string title = string(_title);
                                string author = string(_author);
                                string publisher = string(_publisher);
                                string category = string(_category);
                                string code = string(_code);
                                int quantity = atoi(_quantity);
                                bookService->updateBook(idSelected, code, title, author, publisher, category, quantity);
                                onEditOpen = !onEditOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 90, 250, 40 }, "Title");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 90, 450, 40 }, _title, 64, titleEdit)) {
                                _title = strcpy(_title, _title);
                                titleEdit = !titleEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 170, 250, 40 }, "Code");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 170, 450, 40 }, _code, 64, codeEdit) ) {
                                _code = strcpy(_code, _code);
                                codeEdit = !codeEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 250, 250, 40 }, "Author");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 250, 450, 40 }, _author, 64, authorEdit) ) {
                                _author = strcpy(_author, _author);
                                authorEdit = !authorEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 330, 250, 40 }, "Publisher");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 330, 450, 40 }, _publisher, 64, publisherEdit) ) {
                                _publisher = strcpy(_publisher, _publisher);
                                publisherEdit = !publisherEdit;
                            } 
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 410, 250, 40 }, "Category");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 410, 450, 40 }, _category, 64, categoryEdit) ) {
                                _category = strcpy(_category, _category);
                                categoryEdit = !categoryEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 490, 250, 40 }, "Quantity");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 490, 450, 40 }, _quantity, 64, quantityEdit) ) {
                                _quantity = strcpy(_quantity, _quantity);
                                quantityEdit = !quantityEdit;
                            }
                            EndDrawing();
                        }
                    }
                    onEditOpen = false;
                    if ( GuiButton(deleteBtnBounds, "Delete") && idSelected > 0 ) { 
                        while (!onDeleteOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(deleteTextDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            DrawTextEx(titleFont, "Are you sure to delete?", Vector2{textDivBounds.x + 250, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 200, textDivBounds.y + 250, 150, 40 }, "Yes") ) {
                                bookService->deleteBook(idSelected);
                                onDeleteOpen = !onDeleteOpen;
                                idSelected = -1;
                                rowSelected = -1;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) + 100, textDivBounds.y + 250, 150, 40 }, "No") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onDeleteOpen = false;
                }
            }
            int cnt = 0;
            DrawRectangleRec(tableBounds, LIGHTGRAY);
            DrawTextEx(textFont, "ID", Vector2{tableBounds.x + 10, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Code", Vector2{tableBounds.x + 80, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Title", Vector2{tableBounds.x + 180, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Author", Vector2{tableBounds.x + 430, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Publisher", Vector2{tableBounds.x + 680, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Category", Vector2{tableBounds.x + 930, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Quantity", Vector2{tableBounds.x + 1160, tableBounds.y + 10}, 20, 2, DARKGRAY);

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
            if (scrollRenderTable >= bookCount - renderDefault + 1) {
                scrollRenderTable = bookCount - renderDefault + 1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable = 0;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < renderDefault + scrollRenderTable && i < bookCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width - 30, 30};
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mousePos, rowBounds)) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        } else {
                            idSelected = bookList[i].getBookId();
                            rowSelected = i;
                        }
                    } else if ( !CheckCollisionPointRec(mousePos, editBtnBounds) && !CheckCollisionPointRec(mousePos, deleteBtnBounds) ) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        }
                    }
                }
                if ( bookList[i].getTitle() == "0" && bookList[i].getCode() == "0" && bookList[i].getAuthor() == "0" && bookList[i].getPublisher() == "0" && bookList[i].getCategory() == "0" && bookList[i].getQuantity() == 0 ) {
                    continue;
                }
                if ( rowSelected != i ) {
                    DrawRectangleRec(rowBounds, WHITE);
                } else {
                    DrawRectangleRec(rowBounds, GREEN);
                }
                DrawTextEx(textFont, TextFormat("%d", bookList[i].getBookId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getCode().c_str(),
                        Vector2{rowBounds.x + 80, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getTitle().c_str(),
                        Vector2{rowBounds.x + 180, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getAuthor().c_str(),
                        Vector2{
                            rowBounds.x + 430,
                            rowBounds.y + 5,
                        },
                        20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getPublisher().c_str(),
                        Vector2{rowBounds.x + 680, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getCategory().c_str(),
                        Vector2{rowBounds.x + 930, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, to_string(bookList[i].getQuantity()).c_str(),
                        Vector2{rowBounds.x + 1160, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }
            DrawRectangleRec(scrollMove, GRAY);
            const int move = (int)((scrollMove.height - scrollHeight) / (bookCount - renderDefault));
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

        bool DrawLoginForm(UserService* userService) {
            char* username = new char[64];
            char* password = new char[64];
            char* email = new char[64];
            char* phone = new char[64];
            bool userEdit = false;
            bool passwordEdit = false;
            bool emailEdit = false;
            bool phoneEdit = false;
            username = strcpy(username, "");
            password = strcpy(password, "");
            email = strcpy(email, "");
            phone = strcpy(phone, "");
            Auth auth;
            bool onLogin = false;
            bool onRegister = false;
            InitLogin();
            LoadText();
            while (!WindowShouldClose() && !onLogin)
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTextEx(titleFont, "Login", Vector2{ ( loginWidth / 2 ) - 40, 80 }, 36, 2, DARKGRAY);
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
                if( GuiButton(Rectangle{ ( loginWidth / 2 ) - 120, 400, 100, 40 }, "Login") ) {
                    string _username = string(username);
                    string _password = string(password);
                    List<class User> userList = userService->getUser();
                    for (int i = 0; i < userList.GetLength(); i++) {
                        TraceLog(LOG_INFO, "Id: %d Username: %s, Password: %s Email: %s Phone: %s Role: %s", userList[i].getUserId() , userList[i].getUsername().c_str(), userList[i].getPassword().c_str(), userList[i].getEmail().c_str(), userList[i].getPhone().c_str(), userList[i].getRole()->getRoleName().c_str()); 
                        if ( userList[i].getUsername() == _username && userList[i].getPassword() == _password ) {
                            if ( userList[i].getRole()->getRoleName() == "Admin" ) {
                                roleOfUser = RoleOfUser::_Admin;
                            } else if ( userList[i].getRole()->getRoleName() == "Librarian" ) {
                                roleOfUser = RoleOfUser::_Librarian;
                            } else {
                                roleOfUser = RoleOfUser::_Member;
                            }
                        }
                    }
                    if ( auth.login( _username, _password ) ) {
                        onLogin = !onLogin;
                        CloseWindow();
                        return onLogin;
                    }
                }
                if ( GuiButton(Rectangle{ ( loginWidth / 2 ) + 30, 400, 100, 40 }, "Sign in") ) {
                    while ( !WindowShouldClose() && !onRegister)
                    {
                        BeginDrawing();
                        ClearBackground(RAYWHITE);
                        DrawTextEx(titleFont, "Sign in", Vector2{ ( loginWidth / 2 ) - 40, 80 }, 36, 2, DARKGRAY);
                        GuiLabel(Rectangle{ 50, 180, 250, 40 }, "Username");
                        if (GuiTextBox(Rectangle{ 150, 180, 350, 40 }, username, 64, userEdit)) {
                            username = strcpy(username, username);
                            userEdit = !userEdit;
                        }
                        GuiLabel(Rectangle{ 50, 280, 250, 40 }, "Email");
                        if ( GuiTextBox(Rectangle{ 150, 280, 350, 40 }, email, 64, emailEdit) ) {
                            email = strcpy(email, email);
                            emailEdit = !emailEdit;
                        }
                        GuiLabel(Rectangle{ 50, 380, 250, 40 }, "Phone");
                        if ( GuiTextBox(Rectangle{ 150, 380, 350, 40 }, phone, 64, phoneEdit) ) {
                            phone = strcpy(phone, phone);
                            phoneEdit = !phoneEdit;
                        }
                        GuiLabel(Rectangle{ 50, 480, 250, 40 }, "Password");
                        if ( GuiTextBox(Rectangle{ 150, 480, 350, 40 }, password, 64, passwordEdit) ) {
                            password = strcpy(password, password);
                            passwordEdit = !passwordEdit;
                        }
                        if( GuiButton(Rectangle{ ( loginWidth / 2 ) - 120, 600, 100, 40 }, "Sign in") ) {
                            string _username = string(username);
                            string _password = string(password);
                            string _email = string(email);
                            string _phone = string(phone);
                            int userId = (userService->getUser()).GetLength() + 1;
                            if ( auth.registerUser( userId, _email, _username, _password, _phone ) ) {
                                onRegister = !onRegister;
                                _username = strcpy(username, "");
                                _password = strcpy(password, "");
                                _email = strcpy(email, "");
                                _phone = strcpy(phone, "");
                                continue;
                            }
                        }
                        if( GuiButton(Rectangle{ ( loginWidth / 2 ) + 30, 600, 100, 40 }, "Back") ) {
                            onRegister = !onRegister;
                            continue;
                        }
                        EndDrawing();
                    }
                    if ( !onRegister ) {
                        CloseWindow();
                        return onRegister;
                    }
                }
                onRegister = false;
                EndDrawing();
            }
            CloseWindow();
            return onLogin;
        }

        State DrawBackButton(State currentState) {
            if (GuiButton(Rectangle{tableBounds.x + 1130, tableBounds.y - 50, 150, 40}, GuiIconText(ICON_ARROW_LEFT, "Back"))) {
                return State::Menu;
            }
            return currentState;
        }

        State DrawAdminFunctionBar() {
            DrawTextEx(titleFont, "MENU", Vector2{ ( windowWidth / 2 ) - 50, 150 }, 40, 2, DARKGRAY);
            if (GuiButton(Rectangle{(int)(windowWidth / 2) - 400, 300, 200, 75}, "User")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search user");
                return State::User;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 300, 200, 75 }, "Category")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search category");
                return State::Category;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 300, 200, 75 }, "Publisher")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search publisher");
                return State::Publisher;
            }
            if ( GuiButton(Rectangle{ (int)(windowWidth / 2) - 400, 450, 200, 75 }, "Book") ) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search book");
                return State::Book;
            }
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Borrow Return");
            GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 450, 200, 75 }, "Author");
            if( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 600, 200, 75 }, "Exit") ) { 
                return State::Exit;
            }
            return State::Menu;
        }

        State DrawLibrarianFunctionBar() {
            DrawTextEx(titleFont, "MENU", Vector2{ ( windowWidth / 2 ) - 50, 150 }, 40, 2, DARKGRAY);
            if (GuiButton(Rectangle{(int)(windowWidth / 2) - 400, 300, 200, 75}, "Category")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search category");
                return State::Category;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 300, 200, 75 }, "Publisher")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search publisher");
                return State::Publisher;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 300, 200, 75 }, "Book")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search book");
                return State::Book;
            }
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 400, 450, 200, 75 }, "Borrow Return");
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Author");
            if( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 600, 200, 75 }, "Exit") ) { 
                return State::Exit;
            }
            return State::Menu;
        }

        State DrawMemberFunctionBar() {
            DrawTextEx(titleFont, "MENU", Vector2{ ( windowWidth / 2 ) - 50, 150 }, 40, 2, DARKGRAY);
            if (GuiButton(Rectangle{(int)(windowWidth / 2) - 400, 300, 200, 75}, "Category")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search category");
                return State::Category;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 300, 200, 75 }, "Publisher")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search publisher");
                return State::Publisher;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 300, 200, 75 }, "Book")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search book");
                return State::Book;
            }
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 400, 450, 200, 75 }, "Borrow Return");
            GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Author");
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
