#include <iostream>
#include <string>
using namespace std;
class Auth {
public:
    Auth();
    bool login(string username, string password);
    bool registerUser(string email, string username, string password , string phone);
};