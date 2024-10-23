#include "UserRepository.h"

UserRepository* UserRepository::_userRepository = nullptr;
const char* UserRepository::_userFileName = "../../data/User.txt";
const char* UserRepository::_userTempFileName = "../../data/TempUser.txt";

UserRepository::UserRepository() {
}

UserRepository* UserRepository::initUserRepository() {
    if (_userRepository == nullptr) {
        _userRepository = new UserRepository();
    }
    return _userRepository;
}

UserRepository::~UserRepository() {
}

void UserRepository::addUser(User user) {
    ofstream outFile;
    outFile.open(_userFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Không thể mở file để ghi." << endl;
        return;
    }

    outFile << user.getUserId() << " "
            << user.getEmail() << " "
            << user.getUsername() << " "
            << user.getPassword() << " "
            << user.getPhone() << " " 
            << endl;

    outFile.close();
    cout << "Thêm người dùng thành công!" << endl;
}

void UserRepository::updateUser(User updatedUser) {
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << endl;
        return;
    }

    bool found = false;
    int userId;
    string email, username, password, phone;
    while (inFile >> userId >> email >> username >> password >> phone) {
        if (userId == updatedUser.getUserId()) {
            tempFile << updatedUser.getUserId() << " "
                     << updatedUser.getEmail() << " "
                     << updatedUser.getUsername() << " "
                     << updatedUser.getPassword() << " "
                     << updatedUser.getPhone() << " " 
                     << endl;
            found = true;
        } else {
            tempFile << userId << " "
                     << email << " "
                     << username << " "
                     << password << " "
                     << phone << " " 
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_userFileName); 
        rename(_userTempFileName, _userFileName); 
        cout << "Cập nhật người dùng thành công!" << endl;
    } else {
        remove(_userTempFileName); 
        cout << "Người dùng không tồn tại!" << endl;
    }
}

void UserRepository::deleteUser(int userId){
    ifstream inFile(_userFileName);
    ofstream tempFile(_userTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Không thể mở file để đọc hoặc ghi." << endl;
        return;
    }
    bool found = false;
    int id;
    string email, username, password, phone;
    while (inFile >> id >> email >> username >> password >> phone) {
        if (id == userId) {
            found = true;
        } else {
            tempFile << id << " "
                     << email << " "
                     << username << " "
                     << password << " "
                     << phone << " " 
                     << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(_userFileName); 
        rename(_userTempFileName, _userFileName); 
        cout << "Xóa người dùng thành công!" << endl;
    } else {
        remove(_userTempFileName); 
        cout << "Người dùng không tồn tại!" << endl;
    }
}

User UserRepository::getUserById(int userId) {
    ifstream inFile(_userFileName);
    if (!inFile.is_open()) {
        cerr << "Không thể mở file để đọc." <<  endl;
        return User();
    }
    int id;
    string email, username, password, phone;
    while (inFile >> id >> email >> username >> password >> phone) {
        if (id == userId) {
            inFile.close();
            return User(id, email, username, password, phone);
        }
    }
    inFile.close();
    cout << "Không tìm thấy người dùng với ID này!" << endl;
    return User();
}