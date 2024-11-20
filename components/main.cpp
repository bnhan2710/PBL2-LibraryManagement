#include "./UI_Console/ui.cpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int main(void)
{
    UI ui;
    UserService* userService = UserService::initUserService();
    CategoryService* categoryService = CategoryService::initCategoryService();
    PublisherService* publisherService = PublisherService::initPublisherService();
    if ( !ui.DrawLoginForm() ) {
         return 0;
    }
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
