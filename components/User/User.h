#ifndef USER_H
#define USER_H
#include <string>
#include "../Role/Role.h"
using namespace std;

class User {
private:
    int userId;
    string email;
    string username;
    string password;
    string phone;
    Role* role; 

public:
    User();
    User(int userId, const string& email, const string& username, const string& password, const string& phone, Role* role);
    
    ~User();

    void setUserId(int userId);
    int getUserId() const;

    void setEmail(const string& email);
    string getEmail() const;

    void setUsername(const string& username);
    string getUsername() const;

    void setPassword(const string& password);
    string getPassword() const;

    void setPhone(const string& phone);
    string getPhone() const;

    void setRole(Role* role);
    Role* getRole() const;
};

#endif
