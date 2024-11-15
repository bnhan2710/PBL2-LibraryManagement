#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "./User.h"
#include "./UserRepository.h"
#include "../../utils/List.h"

class UserService {
private:
    static UserService* _userService; 
    UserRepository* _userRepository; 
    List<User> _userList;           

    UserService();
    ~UserService();

public:
    static UserService* initUserService();

    void createUser(const string& username, const string& email, const string& phone, const string& password, Role* role = nullptr);
    void updateUser(int userId, const string& username, const string& email, const string& phone, const string& password, Role* role = nullptr);
    void deleteUser(int userId);
    List<User> getUser(int userId);
    List<User> getUser();

};

#endif
