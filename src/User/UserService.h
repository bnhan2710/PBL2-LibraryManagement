#include "./User.h";

class UserService {
    private:
        static UserService* _userService;
        UserService();
    public:
    static UserService* initUserService();
    ~UserService();

    void createUser(User user);
    void updateUser(User user);
    void deleteUser(int userId);
    User getUserById(int userId);
};
