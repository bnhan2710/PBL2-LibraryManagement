#include "./UI_Console/ui.cpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int main(void)
{
    UI ui;
    UserService* userService = UserService::initUserService();
    CategoryService* categoryService = CategoryService::initCategoryService();
    PublisherService* publisherService = PublisherService::initPublisherService();
    BookService* bookService = BookService::initBookService();
    if ( !ui.DrawLoginForm(userService) ) {
         return 0;
    }
    ui.InitApplication();
    ui.LoadText();
    State currentState = State::Menu;
    TraceLog(LOG_INFO, TextFormat("Role of user: %d", roleOfUser));
    while (!WindowShouldClose() && currentState != State::Exit )
    {
        float wheelMove = GetMouseWheelMove();
        Vector2 mousePos = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currentState) {
            case State::Menu: {
                if (roleOfUser == RoleOfUser::_Admin) {
                    role = new Admin();
                    permissions = role->getPermissions();
                    currentState = ui.DrawAdminFunctionBar();
                } else if (roleOfUser == RoleOfUser::_Librarian) {
                    role = new Librarian();
                    permissions = role->getPermissions();
                    currentState = ui.DrawLibrarianFunctionBar();
                } else if (roleOfUser == RoleOfUser::_Member) {
                    role = new Member();
                    permissions = role->getPermissions();
                    currentState = ui.DrawMemberFunctionBar();
                }
                break;
            }
            case State::User: {
                ui.DrawUserTable( userService, wheelMove, mousePos);
                currentState = ui.DrawBackButton(currentState);
                break;
            }
            case State::Category: {
                ui.DrawCategoryTable( categoryService, wheelMove, mousePos);
                currentState = ui.DrawBackButton(currentState);
                break;
            }
            case State::Publisher: {
                ui.DrawPublisherTable( publisherService, wheelMove, mousePos);
                currentState = ui.DrawBackButton(currentState);
                break;
            }
            case State::Book: {
                ui.DrawBookTable( bookService, wheelMove, mousePos);
                currentState = ui.DrawBackButton(currentState);
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
