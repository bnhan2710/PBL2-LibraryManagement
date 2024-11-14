#ifndef LIBRARIAN_ROLE_H
#define LIBRARIAN_ROLE_H

#include "Role.h"
#include "../../utils/List.h"

class Librarian : public Role {
public:
    string getRoleName() const override ;
    List<string> getPermissions() const override;
};

#endif