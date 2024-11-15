#ifndef ADMIN_ROLE_H
#define ADMIN_ROLE_H
#include "../../utils/List.h"
#include "Role.h"


class Admin : public Role {
public:
    string getRoleName() const override;
    List<string> getPermissions() const override;
};

#endif