#include "auth.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const char* filename = "database/User.txt";

Auth::Auth() {}

bool Auth::login(string username, string password) {
    ifstream file(filename);
    if (!file) {
        cout << "Unable to open file" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, email, user, pass, phone, role;

        getline(ss, id, '|');
        getline(ss, email, '|');
        getline(ss, user, '|');
        getline(ss, pass, '|');
        getline(ss, phone, '|');
        getline(ss, role, '|');

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

bool Auth::registerUser(int id, string email, string username, string password, string phone) {
    ofstream file;
    file.open(filename, ios::app);
    if (!file) {
        cout << "Unable to open file" << endl;
        return false;
    }

    file << id << "|"
         << email << "|"
         << username << "|"
         << password << "|"
         << phone << "|"
         << "Member" << endl;

    file.close();
    return true;
}
