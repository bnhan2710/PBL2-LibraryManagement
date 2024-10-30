#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include "User.h"
#include <iostream>
#include <fstream>
#include "../../utils/List.h"
using namespace std;
class UserRepository {
private:
    static UserRepository* _userRepository;
    static const char* _userFileName;
    static const char* _userTempFileName;
    UserRepository();
public:
    static UserRepository *initUserRepository();
    ~UserRepository();
    void addUser(User user);
    void updateUser(User user);
    void deleteUser(int userId);
    User getUserById(int userId);
    List<User> getAllUsers();
};               
#endif