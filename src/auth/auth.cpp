#include "auth.h"
#include <iostream>
#include <fstream>

using namespace std;

const char* filename = "database/User.txt";


Auth::Auth() {}

bool Auth::login(string username, string password) {
    ifstream file(filename);
    if (!file) {
        cout << "Unable to open file" << endl;
        return false;
    }

    string id, email, user, pass, phone;
    while (file >> id >> email >> user >> pass >> phone) { 
        if (user == username) { 
            if (pass == password) {
                file.close();
                return true;  
            } else {
                cout << "Invalid password" << endl;
                file.close();
                return false;  
            }
        }
    }

    cout << "Invalid username" << endl;
    file.close();
    return false;  
}

bool Auth::registerUser(string email, string username, string password , string phone) {
    ofstream file;
    file.open(filename, ios::app);
    if (!file) {
        cout << "Unable to open file";
        return false;
    }
    file << email << " " << username << " " << password << " " << phone << endl;
    file.close();
    return true;
}