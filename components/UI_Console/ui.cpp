#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "raygui.h"
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>
#include "../User/User.h"
#include "../../utils/List.h"
#include "../User/UserService.h"
#include "../Book/Book.h"
#include "../Book/BookService.h"
#include "../Category/Category.h"
#include "../Category/CategoryService.h"
#include "../Publisher/Publisher.h"
#include "../Publisher/PublisherService.h"
#include "../BorrowReturn/BorrowReturnService.h"
#include "../Author/AuthorService.h"
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
static int userId = -1;
static Role* role = nullptr;
static List<string> permissions;
Font textFont, titleFont;
Texture2D logo;
Image icon;

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
        int searchSelected = 0;
        bool searchEdit = false;
        bool searchProcess = false;
        const int renderDefault = 20;
        int scrollPosition = 0;
        int scrollRenderTable = 0;
        Rectangle tableBounds = { 50, 150, 1300, (float)(30 + renderDefault * 30 )};
        Rectangle scrollMove = { tableBounds.x + tableBounds.width - 30, tableBounds.y + 30, 30, tableBounds.height - 30 };
        Rectangle functionBarBounds = { 0, 0, 300, windowHeight };
        Rectangle textBoxBounds = { tableBounds.x + 150, tableBounds.y - 50, 300, 40 };
        Rectangle addBtnBounds = { tableBounds.x + 590, tableBounds.y - 50, 150, 40 };
        Rectangle editBtnBounds = { tableBounds.x + 770, tableBounds.y - 50, 150, 40 };
        Rectangle deleteBtnBounds = { tableBounds.x + 950, tableBounds.y - 50, 150, 40 };
        Rectangle textDivBounds = { tableBounds.x + 250, tableBounds.y, 800, 600 };
        Rectangle deleteTextDivBounds = { tableBounds.x + 250, tableBounds.y, 800, 350 };
        Rectangle closeDivBounds = { textDivBounds.x + textDivBounds.width - 80, textDivBounds.y + 20, 50, 40 };
    public:
        string toLower(string str) {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            return str;
        }
        void DrawUserTable( UserService* userService, float wheelMove,Vector2 mousePos, string searchBar = "search user") 
        {
            List<class User> userList;
            List<class User> searchList = userService->getUser();
            if ( !searchProcess ) {
                userList = userService->getUser();
            }
            const char* searchOptions = "Username;Email;Role";
            DrawTextEx(titleFont, "User List", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox(textBoxBounds, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), textBoxBounds)) {
                    searchProcess = true;
                    userList.Erase();
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                        searchProcess = false;
                        userList = searchList;
                    } 
                }
            }
            searchBar = string(text);
             for( int i = 0; i < searchList.GetLength(); i++ ) {
                    switch ( searchSelected ) {
                        case 0:
                            if ( toLower(searchList[i].getUsername()).find(toLower(searchBar)) != -1 ) {
                                userList.PushBack(searchList[i]);
                            }
                            break;
                        case 1:
                            if ( toLower(searchList[i].getEmail()).find(toLower(searchBar)) != -1 ) {
                                userList.PushBack(searchList[i]);
                            }
                            break;
                        case 2:
                            if ( toLower(searchList[i].getRole()->getRoleName()).find(toLower(searchBar)) != -1 ) {
                                userList.PushBack(searchList[i]);
                            }
                            break;
                        default:
                            break;
                    }
                }
            int userCount = userList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( userCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
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
            if ( GuiDropdownBox(Rectangle{ textBoxBounds.x + 300, textBoxBounds.y, 120, textBoxBounds.height }, searchOptions, &searchSelected, searchEdit) ) {
                searchEdit = !searchEdit;
            }
        }
            
        void DrawCategoryTable( CategoryService* categoryService, float wheelMove,Vector2 mousePos, string searchBar = "search category") 
        {  
            List<class Category> categoryList;
            List<class Category> searchList = categoryService->getCategory();
            if ( !searchProcess ) {
                categoryList = categoryService->getCategory();
            }
            const char* searchOptions = "CategoryName";
            DrawTextEx(titleFont, "Category", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox(textBoxBounds, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), textBoxBounds)) {
                    searchProcess = true;
                    categoryList.Erase();
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                        searchProcess = false;
                        categoryList = searchList;
                    }
                }
            }
            searchBar = string(text);
            for( int i = 0; i < searchList.GetLength(); i++ ) {
                if ( toLower(searchList[i].getCategoryName()).find(toLower(searchBar)) != -1 ) {
                    categoryList.PushBack(searchList[i]);
                }
            }
            int categoryCount = categoryList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( categoryCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
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
            if ( GuiDropdownBox(Rectangle{ textBoxBounds.x + 300, textBoxBounds.y, 120, textBoxBounds.height }, searchOptions, &searchSelected, searchEdit) ) {
                searchEdit = !searchEdit;
            }
        }

        void DrawPublisherTable( PublisherService* publisherService, float wheelMove,Vector2 mousePos, string searchBar = "search publisher") 
        {
            List<class Publisher> publisherList;
            List<class Publisher> searchList = publisherService->getPublisher();
            if ( !searchProcess ) {
                publisherList = publisherService->getPublisher();
            }
            const char* searchOptions = "PublisherName;Address;ContactInfo";
            DrawTextEx(titleFont, "Publisher", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox(textBoxBounds, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), textBoxBounds)) {
                    searchProcess = true;
                    publisherList.Erase();
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                        searchProcess = false;
                        publisherList = searchList;
                    }
                }
            }
            searchBar = string(text);
            for( int i = 0; i < searchList.GetLength(); i++ ) {
                switch ( searchSelected ) {
                    case 0:
                        if ( toLower(searchList[i].getPublisherName()).find(toLower(searchBar)) != -1 ) {
                            publisherList.PushBack(searchList[i]);
                        }
                        break;
                    case 1:
                        if ( toLower(searchList[i].getAddress()).find(toLower(searchBar)) != -1 ) {
                            publisherList.PushBack(searchList[i]);
                        }
                        break;
                    case 2:
                        if ( toLower(searchList[i].getContactInfo()).find(toLower(searchBar)) != -1 ) {
                            publisherList.PushBack(searchList[i]);
                        }
                        break;
                    default:
                        break;
                }
            }
            int publisherCount = publisherList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( publisherCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
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
                if ( GuiDropdownBox(Rectangle{ textBoxBounds.x + 300, textBoxBounds.y, 120, textBoxBounds.height }, searchOptions, &searchSelected, searchEdit) ) {
                    searchEdit = !searchEdit;
                }
        }

        void DrawBookTable( BookService* bookService, BorrowReturnService* borrowReturnService, AuthorService* authorService, CategoryService* categoryService, PublisherService* publisherService,float wheelMove,Vector2 mousePos, string searchBar = "search book") 
        {
            List<class Book> bookList;
            List<class Book> searchList = bookService->getBook();
            if ( !searchProcess ) {
                bookList = bookService->getBook();
            }
            List<class Author> authorList = authorService->getAuthor();
            List<class Category> categoryList = categoryService->getCategory();
            List<class Publisher> publisherList = publisherService->getPublisher();
            const char* searchOptions = "Title;Code;Author;Category;Publisher";
            for (int i = 0; i < bookList.GetLength(); i++) {
                for (int j = 0; j < authorList.GetLength(); j++) {
                    if (bookList[i].getAuthor().getAuthorId() == authorList[j].getAuthorId()) {
                        bookList[i].setAuthor(authorList[j]);
                    }
                }
                for (int j = 0; j < categoryList.GetLength(); j++) {
                    if (bookList[i].getCategory().getCategoryId() == categoryList[j].getCategoryId()) {
                        bookList[i].setCategory(categoryList[j]);
                    }
                }
                for (int j = 0; j < publisherList.GetLength(); j++) {
                    if (bookList[i].getPublisher().getPublisherId() == publisherList[j].getPublisherId()) {
                        bookList[i].setPublisher(publisherList[j]);
                    }
                }
            }
            DrawTextEx(titleFont, "Book", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox(textBoxBounds, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), textBoxBounds)) {
                    searchProcess = true;
                    bookList.Erase();
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                        searchProcess = false;
                        bookList = searchList;
                    }
                }
            }
            searchBar = string(text);
            for (int i = 0; i < searchList.GetLength(); i++) {
                switch (searchSelected) {
                    case 0:
                        if (toLower(searchList[i].getTitle()).find(toLower(searchBar)) != -1) {
                            bookList.PushBack(searchList[i]);
                        }
                        break;
                    case 1:
                        if (toLower(searchList[i].getCode()).find(toLower(searchBar)) != -1) {
                            bookList.PushBack(searchList[i]);
                        }
                        break;
                    case 2:
                        if (toLower(searchList[i].getAuthor().getAuthorName()).find(toLower(searchBar)) != -1) {
                            bookList.PushBack(searchList[i]);
                        }
                        break;
                    case 3:
                        if (toLower(searchList[i].getCategory().getCategoryName()).find(toLower(searchBar)) != -1) {
                            bookList.PushBack(searchList[i]);
                        }
                        break;
                    case 4:
                        if (toLower(searchList[i].getPublisher().getPublisherName()).find(toLower(searchBar)) != -1) {
                            bookList.PushBack(searchList[i]);
                        }
                        break;
                    default:
                        break;
                }
            }
            int bookCount = bookList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( bookCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
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
                        int selectedCategory = -1;
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
                                int authorId, publisherId, categoryId;
                                authorId = publisherId = categoryId = -1;
                                string title = string(_title);
                                string author = string(_author);
                                string publisher = string(_publisher);
                                string category = string(_category);
                                string code = string(_code);
                                int quantity = atoi(_quantity);
                                for (int i = 0; i < authorList.GetLength(); i++) {
                                    if ( authorList[i].getAuthorName() == author ) {
                                        authorId = i;
                                        break;
                                    }
                                }
                                for (int i = 0; i < publisherList.GetLength(); i++) {
                                    if ( publisherList[i].getPublisherName() == publisher ) {
                                        publisherId = i;
                                        break;
                                    }
                                }
                                for (int i = 0; i < categoryList.GetLength(); i++) {
                                    if ( categoryList[i].getCategoryName() == category ) {
                                        categoryId = i;
                                        break;
                                    }
                                }
                                if ( authorId == -1 || publisherId == -1 || categoryId == -1 ) {
                                    continue;
                                }
                                bookService->addBook(code, title, authorList[authorId], categoryList[categoryId], publisherList[publisherId],  quantity);
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
                            if (GuiButton(Rectangle{ textDivBounds.x + 200, textDivBounds.y + 410, 450, 40 }, _category)) {
                                    categoryEdit = false;
                                    int sum = 0;
                                    Vector2 scrollOffset = { 0, 0 };
                                    Rectangle scrollBox = { textDivBounds.x, textDivBounds.y, textDivBounds.width, textDivBounds.height };
                                    for (int i = 0; i < categoryList.GetLength(); i++) {
                                        sum += strlen( categoryList[i].getCategoryName().c_str() ) * 20;
                                    }
                                    while(!categoryEdit) {  
                                    BeginDrawing();
                                    ClearBackground(RAYWHITE);
                                    DrawRectangleRec( Rectangle{ textDivBounds.x, textDivBounds.y, textDivBounds.width, textDivBounds.height - 100}, WHITE);
                                    DrawTextEx(titleFont, "Select Category", Vector2{textDivBounds.x + 300, textDivBounds.y + 40}, 36, 2, DARKGRAY);
                                    if( GuiButton(closeDivBounds, "X") ) {
                                        categoryEdit = !categoryEdit;
                                    }
                                    Rectangle view;
                                    GuiScrollPanel(
                                        Rectangle{textDivBounds.x + 20,
                                                    textDivBounds.y + 100,
                                                    scrollBox.width - 40,
                                                    textDivBounds.height - 300},
                                        nullptr,
                                        Rectangle{
                                            0,
                                            0,
                                            scrollBox.width - 60,
                                            sum / ( scrollBox.width - 40 ) * 40 + 40},
                                        &scrollOffset, &view);

                                    BeginScissorMode(view.x, view.y, view.width, view.height);
                                    float dis = 0;
                                    int cnt = 0;
                                    float start = scrollBox.x + 30;
                                    for (int i = 0; i < categoryList.GetLength(); i++) {
                                        dis = strlen( categoryList[i].getCategoryName().c_str() ) * 20;
                                        if ( start + dis > scrollBox.x + scrollBox.width - 60 ) {
                                            start = scrollBox.x + 30;
                                            cnt++;
                                        } 
                                        Rectangle item = { start, scrollBox.y + 30 + cnt * 40 + scrollOffset.y, dis, 30};
                                        start += dis + 10;
                                        if ( categoryList[i].getCategoryName() == "0" ) {
                                            start -= dis + 10;
                                            continue;
                                        }
                                        if (GuiButton(item, categoryList[i].getCategoryName().c_str())) {
                                            selectedCategory = i; 
                                            categoryEdit = true;
                                        }
                                    }
                                    EndScissorMode();
                                    if (selectedCategory != -1) {
                                        _category = strcpy(_category, categoryList[selectedCategory].getCategoryName().c_str());
                                    }
                                    EndDrawing();
                                }
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
                        _author = strcpy(_author, bookList[idSelected - 1].getAuthor().getAuthorName().c_str());
                        _publisher = strcpy(_publisher, bookList[idSelected - 1].getPublisher().getPublisherName().c_str());
                        _category = strcpy(_category, bookList[idSelected - 1].getCategory().getCategoryName().c_str());
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
                                int authorId, publisherId, categoryId;
                                authorId = publisherId = categoryId = -1;
                                string title = string(_title);
                                string author = string(_author);
                                string publisher = string(_publisher);
                                string category = string(_category);
                                string code = string(_code);
                                int quantity = atoi(_quantity);
                                for (int i = 0; i < authorList.GetLength(); i++) {
                                    if ( authorList[i].getAuthorName() == author ) {
                                        authorId = i;
                                        break;
                                    }
                                }
                                for (int i = 0; i < publisherList.GetLength(); i++) {
                                    if ( publisherList[i].getPublisherName() == publisher ) {
                                        publisherId = i;
                                        break;
                                    }
                                }
                                for (int i = 0; i < categoryList.GetLength(); i++) {
                                    if ( categoryList[i].getCategoryName() == category ) {
                                        categoryId = i;
                                        break;
                                    }
                                }
                                if ( authorId == -1 || publisherId == -1 || categoryId == -1 ) {
                                    continue;
                                }
                                bookService->updateBook(idSelected, code, title, authorList[authorId], categoryList[categoryId], publisherList[publisherId], quantity);
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
                if ( permissions[i] == "Borrow Books" ) {
                    if ( GuiButton(deleteBtnBounds, "Borrow Books") && idSelected > 0 ) {
                        char *dayBorrow = new char[32]; 
                        char *monthBorrow = new char[32];
                        char *yearBorrow = new char[32];
                        char *dayReturn = new char[32];
                        char *monthReturn = new char[32];
                        char *yearReturn = new char[32];
                        bool dayBorrowEdit = false;
                        bool monthBorrowEdit = false;
                        bool yearBorrowEdit = false;
                        bool dayReturnEdit = false;
                        bool monthReturnEdit = false;
                        bool yearReturnEdit = false;
                        dayBorrow = strcpy(dayBorrow, "");
                        monthBorrow = strcpy(monthBorrow, "");
                        yearBorrow = strcpy(yearBorrow, "");
                        dayReturn = strcpy(dayReturn, "");
                        monthReturn = strcpy(monthReturn, "");
                        yearReturn = strcpy(yearReturn, "");
                        while (!onDeleteOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            DrawTextEx(titleFont, "Borrow Book", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            DrawTextEx(titleFont, "Day Borrow", Vector2{textDivBounds.x + 100, textDivBounds.y + 150}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 220, 100, 40 }, "Day");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 150, textDivBounds.y + 220, 100, 40 }, dayBorrow, 64, dayBorrowEdit)) {
                                dayBorrow = strcpy(dayBorrow, dayBorrow);
                                dayBorrowEdit = !dayBorrowEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 300, textDivBounds.y + 220, 100, 40 }, "Month");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 360, textDivBounds.y + 220, 100, 40 }, monthBorrow, 64, monthBorrowEdit) ) {
                                monthBorrow = strcpy(monthBorrow, monthBorrow);
                                monthBorrowEdit = !monthBorrowEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 510, textDivBounds.y + 220, 100, 40 }, "Year");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 560, textDivBounds.y + 220, 100, 40 }, yearBorrow, 64, yearBorrowEdit) ) {
                                yearBorrow = strcpy(yearBorrow, yearBorrow);
                                yearBorrowEdit = !yearBorrowEdit;
                            }
                            DrawTextEx(titleFont, "Day Return", Vector2{textDivBounds.x + 100, textDivBounds.y + 300}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 370, 100, 40 }, "Day");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 150, textDivBounds.y + 370, 100, 40 }, dayReturn, 64, dayReturnEdit) ) {
                                dayReturn = strcpy(dayReturn, dayReturn);
                                dayReturnEdit = !dayReturnEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 300, textDivBounds.y + 370, 100, 40 }, "Month");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 360, textDivBounds.y + 370, 100, 40 }, monthReturn, 64, monthReturnEdit) ) {
                                monthReturn = strcpy(monthReturn, monthReturn);
                                monthReturnEdit = !monthReturnEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 510, textDivBounds.y + 370, 100, 40 }, "Year");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 560, textDivBounds.y + 370, 100, 40 }, yearReturn, 64, yearReturnEdit) ) {
                                yearReturn = strcpy(yearReturn, yearReturn);
                                yearReturnEdit = !yearReturnEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 70, textDivBounds.y + 500, 150, 40 }, "Borrow") ) {
                                int dayBorrowInt = atoi(dayBorrow);
                                int monthBorrowInt = atoi(monthBorrow);
                                int yearBorrowInt = atoi(yearBorrow);
                                int dayReturnInt = atoi(dayReturn);
                                int monthReturnInt = atoi(monthReturn);
                                int yearReturnInt = atoi(yearReturn);
                                int numDaysOfBorrow = 0;
                                int numDaysOfReturn = 0;
                                int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                                int totalDays = 0;
                                if ( monthBorrowInt > 12 || monthReturnInt > 12 || dayBorrowInt > 31 || dayReturnInt > 31 ) {
                                    continue;
                                }
                                Date borrowDate = Date(dayBorrowInt, monthBorrowInt, yearBorrowInt);
                                if ( dayBorrowInt > borrowDate.monthDays() ) {
                                    continue;
                                }
                                Date returnDate = Date(dayReturnInt, monthReturnInt, yearReturnInt);
                                if ( dayReturnInt > returnDate.monthDays() ) {
                                    continue;
                                }
                                for ( int i = 0; i < yearBorrowInt; i++ ) {
                                    numDaysOfBorrow += (i % 4 == 0 && i % 100 != 0) || (i % 400 == 0) ? 366 : 365; 
                                }
                                for ( int i = 0; i < yearReturnInt; i++ ) {
                                    numDaysOfReturn += (i % 4 == 0 && i % 100 != 0) || (i % 400 == 0) ? 366 : 365; 
                                }
                                for ( int i = 0; i < monthBorrowInt - 1; i++ ) {
                                    numDaysOfBorrow += daysInMonth[i];
                                    if ( i == 1 && (yearBorrowInt % 4 == 0 && yearBorrowInt % 100 != 0) || (yearBorrowInt % 400 == 0) ) {
                                        numDaysOfBorrow++;
                                    }
                                }
                                for ( int i = 0; i < monthReturnInt - 1; i++ ) {
                                    numDaysOfReturn += daysInMonth[i];
                                    if ( i == 1 && (yearReturnInt % 4 == 0 && yearReturnInt % 100 != 0) || (yearReturnInt % 400 == 0) ) {
                                        numDaysOfReturn++;
                                    }
                                }
                                numDaysOfBorrow += dayBorrowInt;
                                numDaysOfReturn += dayReturnInt;
                                totalDays = numDaysOfReturn - numDaysOfBorrow;
                                if ( totalDays < 0 ) {
                                    continue;
                                }
                                borrowReturnService->BorrowBook( userId, idSelected, totalDays, borrowDate, returnDate);
                                onDeleteOpen = !onDeleteOpen;
                                idSelected = -1;
                                rowSelected = -1;
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
                if ( ( bookList[i].getTitle() == "0" && bookList[i].getCode() == "0" && bookList[i].getQuantity() == 0 ) || bookList[i].getAuthor().getAuthorName() == "0" || bookList[i].getPublisher().getPublisherName() == "0" || bookList[i].getCategory().getCategoryName() == "0" ) {
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
                DrawTextEx(textFont, bookList[i].getAuthor().getAuthorName().c_str(),
                        Vector2{
                            rowBounds.x + 430,
                            rowBounds.y + 5,
                        },
                        20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getPublisher().getPublisherName().c_str(),
                        Vector2{rowBounds.x + 680, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, bookList[i].getCategory().getCategoryName().c_str(),
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
            if ( GuiDropdownBox(Rectangle{ textBoxBounds.x + 300, textBoxBounds.y, 120, textBoxBounds.height }, searchOptions, &searchSelected, searchEdit) ) {
                searchEdit = !searchEdit;
            }
        }

        void DrawBorrowReturnTable( BorrowReturnService* borrowReturnService, UserService* userService, BookService* bookService, float wheelMove,Vector2 mousePos, string searchBar = "search borrow list") 
        {
            List<class BorrowReturn> borrowReturnList; 
            List<class BorrowReturn> searchList = roleOfUser == RoleOfUser::_Member ? borrowReturnService->getBorrowList(userId) : borrowReturnService->getBorrowList();
            if ( !searchProcess ) {
                borrowReturnList = roleOfUser == RoleOfUser::_Member ? borrowReturnService->getBorrowList(userId) : borrowReturnService->getBorrowList();
            }
            const char *searchOptions = "BookTitle;Username;BorrowDate;ReturnDate;DayLeft;Status";
            DrawTextEx(titleFont, "Borrow Return List", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox( Rectangle{ textBoxBounds.x + 150, textBoxBounds.y, textBoxBounds.width, textBoxBounds.height }, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ textBoxBounds.x + 150, textBoxBounds.y, textBoxBounds.width, textBoxBounds.height}) ) {
                    searchProcess = true;
                    borrowReturnList.Erase();
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                        searchProcess = false;
                        borrowReturnList = searchList;
                    }
                }
            }
            searchBar = string(text);
            for (int i = 0; i < searchList.GetLength(); i++) {
                switch (searchSelected) {
                    case 0:
                        if ( toLower(bookService->getBook( searchList[i].getBookId() )[0].getTitle()).find(searchBar) != -1) {
                            borrowReturnList.PushBack(searchList[i]);
                        }
                        break;
                    case 1:
                        if ( toLower(userService->getUser( searchList[i].getUserId() )[0].getUsername()).find(searchBar) != -1) {
                            borrowReturnList.PushBack(searchList[i]);
                        }
                        break;
                    case 2:
                        if (searchList[i].getBorrowAt().getFormattedDate().find(searchBar) != -1) {
                            borrowReturnList.PushBack(searchList[i]);
                        }
                        break;
                    case 3:
                        if (searchList[i].getReturnAt().getFormattedDate().find(searchBar) != -1) {
                            borrowReturnList.PushBack(searchList[i]);
                        }
                        break;
                    case 4:
                        if (to_string(searchList[i].getNumOfDays()).find(searchBar) != -1) {
                            borrowReturnList.PushBack(searchList[i]);
                        }
                        break;
                    case 5:
                        if ( searchList[i].getStatus() == 0 && toLower("Borrowed").find(toLower(searchBar)) != -1 ) {
                            borrowReturnList.PushBack(searchList[i]);
                        } else if ( searchList[i].getStatus() == 1 && toLower("Returned").find(toLower(searchBar)) != -1) {
                            borrowReturnList.PushBack(searchList[i]);
                        }
                        break;
                }
            }
            int borrowReturnCount = borrowReturnList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( borrowReturnCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
            for( int i = 0; i < permissions.GetLength(); i++ ) {
                if ( permissions[i] == "Return Books" ) {
                    if ( GuiButton(deleteBtnBounds, "Return Books") && idSelected > 0 ) { 
                        while (!onDeleteOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(deleteTextDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onDeleteOpen = !onDeleteOpen;
                            }
                            DrawTextEx(titleFont, "Are you sure to return this book?", Vector2{textDivBounds.x + 150, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 200, textDivBounds.y + 250, 150, 40 }, "Yes") ) {
                                cout << idSelected << endl;
                                borrowReturnService->ReturnBook(idSelected);
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
            DrawTextEx(textFont, "Book Tite", Vector2{tableBounds.x + 100, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Username", Vector2{tableBounds.x + 380, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "BorrowDate", Vector2{tableBounds.x + 550, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "ReturnDate", Vector2{tableBounds.x + 750, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Day left", Vector2{tableBounds.x + 1000, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "status", Vector2{tableBounds.x + 1150, tableBounds.y + 10}, 20, 2, DARKGRAY);

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
            if (scrollRenderTable >= borrowReturnCount - renderDefault + 1) {
                scrollRenderTable = borrowReturnCount - renderDefault + 1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable = 0;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < renderDefault + scrollRenderTable && i < borrowReturnCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width - 30, 30};
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mousePos, rowBounds)) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        } else {
                            idSelected = borrowReturnList[i].getId();
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
                string status = borrowReturnList[i].getStatus() == 0 ? "Borrowed" : "Returned";
                DrawTextEx(textFont, TextFormat("%d", borrowReturnList[i].getId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, bookService->getBook( borrowReturnList[i].getBookId() )[0].getTitle().c_str(),
                        Vector2{rowBounds.x + 100, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, userService->getUser( borrowReturnList[i].getUserId() )[0].getUsername().c_str(),
                        Vector2{rowBounds.x + 380, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, borrowReturnList[i].getBorrowAt().getFormattedDate().c_str(),
                        Vector2{ rowBounds.x + 550, rowBounds.y + 5, }, 20, 2, DARKGRAY);
                DrawTextEx(textFont, borrowReturnList[i].getReturnAt().getFormattedDate().c_str(),
                        Vector2{rowBounds.x + 750, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, TextFormat("%d", borrowReturnList[i].getNumOfDays()),
                        Vector2{rowBounds.x + 1000, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, status.c_str(),
                        Vector2{rowBounds.x + 1150, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }
            DrawRectangleRec(scrollMove, GRAY);
            const int move = (int)((scrollMove.height - scrollHeight) / (borrowReturnCount - renderDefault));
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
            if ( GuiDropdownBox(Rectangle{ textBoxBounds.x + 450, textBoxBounds.y, 120, textBoxBounds.height }, searchOptions, &searchSelected, searchEdit) ) {
                searchEdit = !searchEdit;
            }
        }

       
        void DrawAuthorTable( AuthorService* authorService, float wheelMove,Vector2 mousePos, string searchBar = "search author") 
        {
            List<class Author> authorList;
            List<class Author> searchList = authorService->getAuthor();
            if ( !searchProcess ) {
                authorList = authorService->getAuthor();
            }
            const char *searchOptions = "AuthorName;AuthorInfo;BirthDate";
            DrawTextEx(titleFont, "Author", Vector2{tableBounds.x, tableBounds.y - 50}, 36, 2, DARKGRAY);
            GuiTextBox(textBoxBounds, text, 64, editMode);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(GetMousePosition(), textBoxBounds)) {
                    searchProcess = true;
                    authorList.Erase();
                    if ( strcmp(text, searchBar.c_str()) == 0 ) {
                        text = strcpy(text, "");
                    }
                    editMode = !editMode;
                } else {
                    editMode = false;
                    if ( strcmp(text, "") == 0 ) {
                        text = strcpy(text, searchBar.c_str());
                        searchProcess = false;
                        authorList = searchList;
                    }
                }
            }
            for (int i = 0; i < searchList.GetLength(); i++) {
                switch (searchSelected) {
                    case 0:
                        if ( toLower(searchList[i].getAuthorName()).find(searchBar) != -1) {
                            authorList.PushBack(searchList[i]);
                        }
                        break;
                    case 1:
                        if ( toLower(searchList[i].getAuthorInfo()).find(searchBar) != -1) {
                            authorList.PushBack(searchList[i]);
                        }
                        break;
                    case 2:
                        if (searchList[i].getBirthDate().getFormattedDate().find(searchBar) != -1) {
                            authorList.PushBack(searchList[i]);
                        }
                        break;
                }
            }
            searchBar = string(text);
            int authorCount = authorList.GetLength();
            const float scrollHeight = scrollMove.height - ( 30 * (int)( authorCount / ( renderDefault + 1 ) ) );
            Rectangle scrollBounds = { scrollMove.x, scrollMove.y, 30, scrollHeight };
            for( int i = 0; i < permissions.GetLength(); i++ ) {
                if ( permissions[i] == "Manage Authors" ) {
                    if( GuiButton(addBtnBounds, "Add Author") ) {
                        char *_authorName = new char[32];
                        char *_authorInfo = new char[32];
                        char *day = new char[32];
                        char *month = new char[32];
                        char *year = new char[32];
                        bool authorEdit = false;
                        bool authorInfoEdit = false;
                        bool dayEdit = false;
                        bool monthEdit = false;
                        bool yearEdit = false;
                        _authorName = strcpy(_authorName, "");
                        _authorInfo= strcpy(_authorInfo, "");
                        day = strcpy(day, "");
                        month = strcpy(month, "");
                        year = strcpy(year, "");
                        while (!onAddOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onAddOpen = !onAddOpen;
                            }
                            DrawTextEx(titleFont, "Add Author", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 150, 250, 40 }, "Author Name");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 150, 450, 40 }, _authorName, 64, authorEdit)) {
                                _authorName = strcpy(_authorName, _authorName);
                                authorEdit = !authorEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 230, 250, 40 }, "AuthorInfo");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 230, 450, 40 }, _authorInfo, 64, authorInfoEdit) ) {
                                _authorInfo = strcpy(_authorInfo, _authorInfo);
                                authorInfoEdit = !authorInfoEdit;
                            }
                            DrawTextEx(titleFont, "Birth Date", Vector2{textDivBounds.x + 100, textDivBounds.y + 300}, 30, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 370, 100, 40 }, "Day");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 150, textDivBounds.y + 370, 100, 40 }, day, 64, dayEdit) ) {
                                day = strcpy(day, day);
                                dayEdit = !dayEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 300, textDivBounds.y + 370, 100, 40 }, "Month");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 360, textDivBounds.y + 370, 100, 40 }, month, 64, monthEdit) ) {
                                month = strcpy(month, month);
                                monthEdit = !monthEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 510, textDivBounds.y + 370, 100, 40 }, "Year");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 560, textDivBounds.y + 370, 100, 40 }, year, 64, yearEdit) ) {
                                year = strcpy(year, year);
                                yearEdit = !yearEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Add") ) {
                                string authorName = string(_authorName);
                                string authorInfo = string(_authorInfo);
                                int dayInt = atoi(day);
                                int monthInt = atoi(month);
                                int yearInt = atoi(year);
                                Date birthDate = Date(dayInt, monthInt, yearInt);
                                authorService->addAuthor(authorName, birthDate, authorInfo);
                                onAddOpen = !onAddOpen;
                            }
                            EndDrawing();
                        }
                    }
                    onAddOpen = false;
                    if ( GuiButton(editBtnBounds, "Edit") && idSelected > 0 ) {
                        char *_authorName = new char[32];
                        char *_authorInfo = new char[32];
                        char *day = new char[32];
                        char *month = new char[32];
                        char *year = new char[32];
                        bool authorEdit = false;
                        bool authorInfoEdit = false;
                        bool dayEdit = false;
                        bool monthEdit = false;
                        bool yearEdit = false;
                        int _day, _month, _year, cnt = 0;
                        string birthDateStr = authorList[idSelected - 1].getBirthDate().getFormattedDate();
                        _authorName = strcpy(_authorName, authorList[idSelected - 1].getAuthorName().c_str());
                        _authorInfo = strcpy(_authorInfo, authorList[idSelected - 1].getAuthorInfo().c_str());
                        for( int i = 0; i < birthDateStr.length(); i++ ) {
                            if ( birthDateStr[i] == '-' && cnt == 0 ) {
                                _day = atoi(birthDateStr.substr(0, i).c_str());
                                cnt = i + 1;
                            } else if ( birthDateStr[i] == '-' && cnt != 0 ) {
                                _month = atoi(birthDateStr.substr(cnt, i).c_str());
                                _year = atoi(birthDateStr.substr(i + 1, birthDateStr.length() - i).c_str());
                            }
                        }
                        day = strcpy(day, to_string(_day).c_str());
                        month = strcpy(month, to_string(_month).c_str());
                        year = strcpy(year, to_string(_year).c_str());
                        cnt = 0;
                        while (!onEditOpen)
                        {
                            BeginDrawing();
                            ClearBackground(GRAY);
                            DrawRectangleRec(textDivBounds, WHITE);
                            if( GuiButton(closeDivBounds, "X") ) {
                                onEditOpen = !onEditOpen;
                            }
                            DrawTextEx(titleFont, "Edit Author", Vector2{textDivBounds.x + 320, textDivBounds.y + 50}, 36, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 150, 250, 40 }, "Author Name");
                            if (GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 150, 450, 40 }, _authorName, 64, authorEdit)) {
                                _authorName = strcpy(_authorName, _authorName);
                                authorEdit = !authorEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 230, 250, 40 }, "AuthorInfo");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 250, textDivBounds.y + 230, 450, 40 }, _authorInfo, 64, authorInfoEdit) ) {
                                _authorInfo = strcpy(_authorInfo, _authorInfo);
                                authorInfoEdit = !authorInfoEdit;
                            }
                            DrawTextEx(titleFont, "Birth Date", Vector2{textDivBounds.x + 100, textDivBounds.y + 300}, 30, 2, DARKGRAY);
                            GuiLabel(Rectangle{ textDivBounds.x + 100, textDivBounds.y + 370, 100, 40 }, "Day");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 150, textDivBounds.y + 370, 100, 40 }, day, 64, dayEdit) ) {
                                day = strcpy(day, day);
                                dayEdit = !dayEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 300, textDivBounds.y + 370, 100, 40 }, "Month");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 360, textDivBounds.y + 370, 100, 40 }, month, 64, monthEdit) ) {
                                month = strcpy(month, month);
                                monthEdit = !monthEdit;
                            }
                            GuiLabel(Rectangle{ textDivBounds.x + 510, textDivBounds.y + 370, 100, 40 }, "Year");
                            if ( GuiTextBox(Rectangle{ textDivBounds.x + 560, textDivBounds.y + 370, 100, 40 }, year, 64, yearEdit) ) {
                                year = strcpy(year, year);
                                yearEdit = !yearEdit;
                            }
                            if( GuiButton(Rectangle{ ( windowWidth / 2 ) - 50, textDivBounds.y + 460, 150, 40 }, "Save") ) {
                                string authorName = string(_authorName);
                                string authorInfo = string(_authorInfo);
                                int dayInt = atoi(day);
                                int monthInt = atoi(month);
                                int yearInt = atoi(year);
                                Date birthDate = Date(dayInt, monthInt, yearInt);
                                authorService->updateAuthor( idSelected, authorName, birthDate, authorInfo);
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
                                authorService->deleteAuthor(idSelected);
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
            DrawTextEx(textFont, "Author Name", Vector2{tableBounds.x + 100, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "Author Info", Vector2{tableBounds.x + 500, tableBounds.y + 10}, 20, 2, DARKGRAY);
            DrawTextEx(textFont, "birthDate", Vector2{tableBounds.x + 900, tableBounds.y + 10}, 20, 2, DARKGRAY);

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
            if (scrollRenderTable >= authorCount - renderDefault + 1) {
                scrollRenderTable = authorCount - renderDefault + 1;
            }

            if (scrollRenderTable < 0) {
                scrollRenderTable = 0;
                cnt = 0;
            }
            for (int i = scrollRenderTable; i < renderDefault + scrollRenderTable && i < authorCount; i++) {
                Rectangle rowBounds = {tableBounds.x, tableBounds.y + (cnt + 1) * 30, tableBounds.width - 30, 30};
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mousePos, rowBounds)) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        } else {
                            idSelected = authorList[i].getAuthorId();
                            rowSelected = i;
                        }
                    } else if ( !CheckCollisionPointRec(mousePos, editBtnBounds) && !CheckCollisionPointRec(mousePos, deleteBtnBounds) ) {
                        if (rowSelected == i) {
                            idSelected = -1;
                            rowSelected = -1;
                        }
                    }
                }
                if ( authorList[i].getAuthorName() == "0" && authorList[i].getAuthorInfo() == "0" ) {
                    continue;
                }
                if ( rowSelected != i ) {
                    DrawRectangleRec(rowBounds, WHITE);
                } else {
                    DrawRectangleRec(rowBounds, GREEN);
                }
                DrawTextEx(textFont, TextFormat("%d", authorList[i].getAuthorId()),
                        Vector2{rowBounds.x + 10, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, authorList[i].getAuthorName().c_str(),
                        Vector2{rowBounds.x + 100, rowBounds.y + 5}, 20, 2, DARKGRAY);
                DrawTextEx(textFont, authorList[i].getAuthorInfo().c_str(),
                        Vector2{
                            rowBounds.x + 500,
                            rowBounds.y + 5,
                        },
                        20, 2, DARKGRAY);
                DrawTextEx(textFont, authorList[i].getBirthDate().getFormattedDate().c_str(),
                        Vector2{rowBounds.x + 900, rowBounds.y + 5}, 20, 2, DARKGRAY);
                ++cnt;
            }
                DrawRectangleRec(scrollMove, GRAY);
                int move = (int)((scrollMove.height - scrollHeight) /
                                (authorCount - renderDefault));
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
                if ( GuiDropdownBox(Rectangle{ textBoxBounds.x + 300, textBoxBounds.y, 120, textBoxBounds.height }, searchOptions, &searchSelected, searchEdit) ) {
                    searchEdit = !searchEdit;
                }
        }

        void LoadText() {
            textFont = LoadFontEx("components/UI_Console/font/NotoSans-Regular.ttf", 20, nullptr, 0);
            titleFont = LoadFontEx("components/UI_Console/font/NotoSans-Regular.ttf", 40, nullptr, 0);
            icon = LoadImage("components/UI_Console/logo.png");
            logo = LoadTextureFromImage(icon);
            UnloadImage(icon);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
            GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(Color{ 39, 229, 245, 26 }));
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Color{ 39, 229, 245, 26 }));
            GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(Color{ 0, 255, 0, 255 }));
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
                        if ( userList[i].getUsername() == _username && userList[i].getPassword() == _password ) {
                            userId = userList[i].getUserId();
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
                searchSelected = 0;
                searchEdit = false;
                searchProcess = false;
                return State::Menu;
            }
            return currentState;
        }

        State DrawAdminFunctionBar() {
            DrawTextureEx(logo, Vector2{ (int)(windowWidth / 2) - 40, 30 }, 0.0f, 0.5f, WHITE);
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
            if ( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Borrow Return") ) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search borrow list");
                return State::BorrowReturn;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) + 200, 450, 200, 75 }, "Author")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search author");
                return State::Author;
            }
            if( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 600, 200, 75 }, "Exit") ) { 
                return State::Exit;
            }
            return State::Menu;
        }

        State DrawLibrarianFunctionBar() {
            DrawTextureEx(logo, Vector2{ (int)(windowWidth / 2) - 40, 30 }, 0.0f, 0.5f, WHITE);
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
            if ( GuiButton(Rectangle{ (int)(windowWidth / 2) - 400, 450, 200, 75 }, "Borrow Return") ) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search borrow list");
                return State::BorrowReturn;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Author")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search author");
                return State::Author;
            }
            if( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 600, 200, 75 }, "Exit") ) { 
                return State::Exit;
            }
            return State::Menu;
        }

        State DrawMemberFunctionBar() {
            DrawTextureEx(logo, Vector2{ (int)(windowWidth / 2) - 40, 30 }, 0.0f, 0.5f, WHITE);
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
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) - 400, 450, 200, 75 }, "Borrow Return")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search borrow list");
                return State::BorrowReturn;
            }
            if (GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 450, 200, 75 }, "Author")) {
                scrollPosition = 0;
                scrollRenderTable = 0;
                text = strcpy(text, "search author");
                return State::Author;
            }
            if( GuiButton(Rectangle{ (int)(windowWidth / 2) - 100, 600, 200, 75 }, "Exit") ) { 
                return State::Exit;
            }
            return State::Menu;
        }

        void End() {
            onAddOpen = false;
            onEditOpen = false;
            UnloadImage(icon);
            UnloadFont(textFont);
            UnloadFont(titleFont);
        }
};
