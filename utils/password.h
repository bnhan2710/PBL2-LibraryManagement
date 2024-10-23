#include <string>
#include <iostream>
using namespace std;

class PasswordUtil{
public:
    static string hashPassword(const string& password);
    static bool comparePassword(const string& password,string& hashedPassword);
};

