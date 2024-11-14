#ifndef ROLE_H
#define ROLE_H
#include "../../utils/List.h"
#include <string>
#include <vector>

using namespace std;

class Role {
public:
    virtual string getRoleName() const = 0; 
    virtual List<string> getPermissions() const = 0; 
    virtual ~Role() {}  
};

#endif
