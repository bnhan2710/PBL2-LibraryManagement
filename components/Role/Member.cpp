#include "Member.h"

string MemberRole::getRoleName() const {
    return "Member";
}

List<string> MemberRole::getPermissions() const {     
     List<string> permissions; 
     permissions.InsertLast("View Books");
     permissions.InsertLast("Borrow Books"); 
     permissions.InsertLast("Return Books");
     permissions.InsertLast("View Borrowed Books");
     return permissions; 
}