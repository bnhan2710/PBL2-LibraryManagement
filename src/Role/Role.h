#ifndef ROLE_H
#define ROLE_H
#include <string>
using namespace std;
class Role {
private:
    string roleId;
    string roleName;
public:
    Role();
    Role(string roleId, string roleName);
    void setRoleId(string roleId);
    string getRoleId();
    void setRoleName(string roleName);
    string getRoleName();
};
#endif