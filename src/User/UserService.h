#ifndef USERSERVICE_H
#define USERSERVICE_H
#include "./User.h"
#include "./UserRepository.h"
class UserService {
    private:
        static UserService* _userService;
        UserRepository* _userRepository;
        UserService();
    public:
    static UserService* initUserService();
    ~UserService();
    void registerAccount(User user);
    void updateUser(User user);
    void deleteUser(int userId);
    User getUserById(int userId);
};
#endif
