#include "Librarian.h"

string Librarian::getRoleName() const {
    return "Librarian";
}

List<string> Librarian::getPermissions() const {     
     List<string> permissions; 
     permissions.InsertLast("Manage Books"); 
     permissions.InsertLast("Manage Category");
     permissions.InsertLast("Manage Author");
     permissions.InsertLast("Manage Publisher");
     return permissions; 
}