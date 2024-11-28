#include "Librarian.h"

string Librarian::getRoleName() const {
    return "Librarian";
}

List<string> Librarian::getPermissions() const {     
    List<string> permissions; 
    permissions.InsertLast("Manage Books"); 
    permissions.InsertLast("Manage Categories");
    permissions.InsertLast("Manage Authors");
    permissions.InsertLast("Manage Publishers");
    return permissions; 
}