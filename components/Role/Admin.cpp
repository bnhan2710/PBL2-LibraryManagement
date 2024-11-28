#include "Admin.h"

string Admin::getRoleName() const {
    return "Admin";
}

List<string> Admin::getPermissions() const {     
    List<string> permissions; 
    permissions.InsertLast("Manage Users"); 
    permissions.InsertLast("Manage Books"); 
    permissions.InsertLast("Manage Categories");
    permissions.InsertLast("Manage Authors");
    permissions.InsertLast("Manage Publishers");
    return permissions; 
}

