#include "Admin.h"

string Admin::getRoleName() const {
    return "Admin";
}

List<string> Admin::getPermissions() const {     
     List<string> permissions; 
     permissions.InsertLast("Manage Users"); 
     permissions.InsertLast("Manage Books"); 
     permissions.InsertLast("Manage Category");
     permissions.InsertLast("Manage Author");
     permissions.InsertLast("Manage Publisher");
     return permissions; 
}

