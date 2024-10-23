#include "./User.h"

class UserService {
    private:
        static UserService* _userService;
        UserService();
    public:
    static UserService* initUserService();
    ~UserService();

    void registerAccount(User user);
    void updateUser(User user);
    void deleteUser(int userId);
    User getUserById(int userId);
};
