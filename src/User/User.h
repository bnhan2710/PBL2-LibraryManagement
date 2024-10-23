#ifndef USER_H
#define USER_H
#include <string>
// #include "Role.h"
using namespace std;
class User {
private:
    int userId;
    string email;
    string username;
    string password;
    string phone;
    // Role role;
public:
    User();
    User( int userId, string& email, string& username, string& password, string& phone );
    void setUserId( int userId );
    int getUserId();
    void setEmail( string email );
    string getEmail();
    void setUsername( string username );
    string getUsername();
    void setPassword( string password );
    string getPassword();
    void setPhone( string phone );
    string getPhone();
    // void setRole( Role role );
    // Role getRole();
};
#endif