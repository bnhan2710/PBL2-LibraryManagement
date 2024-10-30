#include <iostream>
using namespace std;

class UI {
    private:
    void Separator() {
        cout << "=====================================\n";
    }

    public:


    void MainMenu() {
        Separator();
        cout << "             MAIN MENU               \n";
        Separator();
        cout << "  1. User\n";
        cout << "  2. Category\n";
        cout << "  3. Publisher\n";
        cout << "  4. Book\n";
        cout << "  5. Exit\n";
        Separator();
        cout << endl;
    }

    void UserMenu() {
        Separator();
        cout << "             USER MENU               \n";
        Separator();
        cout << "  1. Add\n";
        cout << "  2. Update\n";
        cout << "  3. Delete\n";
        cout << "  4. Show\n";
        cout << "  5. Exit\n";
        Separator();
        cout << endl;
    }

    void CategoryMenu() {
        Separator();
        cout << "           CATEGORY MENU             \n";
        Separator();
        cout << "  1. Add\n";
        cout << "  2. Update\n";
        cout << "  3. Delete\n";
        cout << "  4. Show\n";
        cout << "  5. Exit\n";
        Separator();
        cout << endl;
    }

    void PublisherMenu() {
        Separator();
        cout << "           PUBLISHER MENU            \n";
        Separator();
        cout << "  1. Add\n";
        cout << "  2. Update\n";
        cout << "  3. Delete\n";
        cout << "  4. Show\n";
        cout << "  5. Exit\n";
        Separator();
        cout << endl;
    }

    void BookMenu() {
        Separator();
        cout << "             BOOK MENU               \n";
        Separator();
        cout << "  1. Add\n";
        cout << "  2. Update\n";
        cout << "  3. Delete\n";
        cout << "  4. Show\n";
        cout << "  5. Exit\n";
        Separator();
        cout << endl;
    }

    void AuthorMenu() {
        Separator();
        cout << "            AUTHOR MENU              \n";
        Separator();
        cout << "  1. Add\n";
        cout << "  2. Update\n";
        cout << "  3. Delete\n";
        cout << "  4. Show\n";
        cout << "  5. Exit\n";
        Separator();
        cout << endl;
    }
};
