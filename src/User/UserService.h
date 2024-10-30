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
    public:
    static UserService* initUserService();
    ~UserService();
    void createUser();
    void updateUser();
    void deleteUser();
    User getUserById();
};
#endif
