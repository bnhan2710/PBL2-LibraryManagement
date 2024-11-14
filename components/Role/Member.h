#ifndef MEMBER_ROLE_H
#define MEMBER_ROLE_H

#include "Role.h"
#include "../../utils/List.h"

class MemberRole : public Role {
public:
    string getRoleName() const override;
    List<string> getPermissions() const override;
};

#endif