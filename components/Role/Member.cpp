#include "Member.h"

string Member::getRoleName() const {
    return "Member";
}

List<string> Member::getPermissions() const {     
    List<string> permissions; 
    permissions.InsertLast("View Publishers");
    permissions.InsertLast("View Categories");
    permissions.InsertLast("View Authors");
    permissions.InsertLast("View Books");
    permissions.InsertLast("View Authors");
    permissions.InsertLast("View Borrowed Books");
    permissions.InsertLast("Borrow Books"); 
    permissions.InsertLast("Return Books");
    return permissions; 
}
