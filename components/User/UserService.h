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
    void createUser( string username, string email, string phone, string password );
    void updateUser( int userId, string username, string email, string phone, string password );
    void deleteUser();
    List<User> getUser( int );
    List<User> getUser();
};
#endif