#include "Role.h"

Role::Role() {
    this->roleId = "";
    this->roleName = "";
}

Role::Role(string& roleId, string& roleName) {
    this->roleId = roleId;
    this->roleName = roleName;
}

void Role::setRoleId(string roleId) {
    this->roleId = roleId;
}

string Role::getRoleId() {
    return this->roleId;
}

void Role::setRoleName(string roleName) {
    this->roleName = roleName;
}

string Role::getRoleName() {
    return this->roleName;
}
