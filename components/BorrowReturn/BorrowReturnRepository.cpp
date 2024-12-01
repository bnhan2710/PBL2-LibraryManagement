#include "BorrowReturnRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>

BorrowReturnRepository* BorrowReturnRepository::_borrowReturnRepository = nullptr;
const char* BorrowReturnRepository::_borrowReturnFileName = "database/BorrowReturn.txt";
const char* BorrowReturnRepository::_borrowReturnTempFileName = "database/TempBorrowReturn.txt";

BorrowReturnRepository::BorrowReturnRepository() {}

BorrowReturnRepository* BorrowReturnRepository::initBorrowReturnRepository() {
    if (_borrowReturnRepository == nullptr) {
        _borrowReturnRepository = new BorrowReturnRepository();
    }
    return _borrowReturnRepository;
}

BorrowReturnRepository::~BorrowReturnRepository() {}

void BorrowReturnRepository::addBorrowReturn(const BorrowReturn& borrowReturn) {
    ofstream outFile;
    outFile.open(_borrowReturnFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }
    string status = borrowReturn.getStatus() == Status::BORROWING ? "BORROWING" : "RETURNED";

    outFile << borrowReturn.getId() << "|"
            << borrowReturn.getUserId() << "|"
            << borrowReturn.getBookId() << "|"
            << borrowReturn.getBorrowAt().getFormattedDate() << "|"
            << borrowReturn.getReturnAt().getFormattedDate() << "|"
            << borrowReturn.getNumOfDays() << "|"
            << status << endl;

    outFile.close();
    cout << "Borrow book successful" << endl;
}

void BorrowReturnRepository::updateBorrowReturn(const BorrowReturn& borrowReturn ) {
    ifstream inFile(_borrowReturnFileName);
    ofstream tempFile(_borrowReturnTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, userIdStr, bookIdStr, borrowAtStr, returnAtStr, numOfDaysStr, status;

        getline(ss, idStr, '|');
        getline(ss, userIdStr, '|');
        getline(ss, bookIdStr, '|');
        getline(ss, borrowAtStr, '|');
        getline(ss, returnAtStr, '|');
        getline(ss, numOfDaysStr, '|');
        getline(ss, status, '|');
        int id = atoi(idStr.c_str());

        if (id == borrowReturn.getId()) {
            string status_ = borrowReturn.getStatus() == Status::BORROWING ? "BORROWING" : "RETURNED";
            cout << status << status_ << endl;
            tempFile << borrowReturn.getId() << "|"
                    << borrowReturn.getUserId() << "|"
                    << borrowReturn.getBookId() << "|"
                    << borrowReturn.getBorrowAt().getFormattedDate() << "|"
                    << borrowReturn.getReturnAt().getFormattedDate() << "|"
                    << borrowReturn.getNumOfDays() << "|"
                    << status_ << endl;
            found = true;
        } else {
            tempFile << idStr << "|" 
                     << userIdStr << "|" 
                     << bookIdStr << "|" 
                     << borrowAtStr << "|" 
                     << returnAtStr << "|" 
                     << numOfDaysStr << "|" 
                     << status << endl; 
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_borrowReturnFileName);
        rename(_borrowReturnTempFileName, _borrowReturnFileName);
        cout << "Updated borrow return successful" << endl;
    } else {
        remove(_borrowReturnTempFileName);
        cout << "Borrow return not found" << endl;
    }
}

void BorrowReturnRepository::deleteBorrowReturn(int borrowReturnId) {
    ifstream inFile(_borrowReturnFileName);
    ofstream tempFile(_borrowReturnTempFileName, ios::app);
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, userIdStr, bookIdStr, borrowAtStr, returnAtStr, numOfDaysStr, status;

        getline(ss, idStr, '|');
        getline(ss, userIdStr, '|');
        getline(ss, bookIdStr, '|');
        getline(ss, borrowAtStr, '|');
        getline(ss, returnAtStr, '|');
        getline(ss, numOfDaysStr, '|');
        getline(ss, status, '|');

        int id = atoi(idStr.c_str());

        if (id == borrowReturnId) {
            found = true;
        } else {
            tempFile << idStr << "|" 
                     << userIdStr << "|" 
                     << bookIdStr << "|" 
                     << borrowAtStr << "|" 
                     << returnAtStr << "|" 
                     << numOfDaysStr << "|" 
                     << status << endl;
        }
    }
    inFile.close();
    tempFile.close();

    if (found) {
        remove(_borrowReturnFileName);
        rename(_borrowReturnTempFileName, _borrowReturnFileName);
        cout << "Deleted borrow return successful" << endl;
    } else {
        remove(_borrowReturnTempFileName);
        cout << "Borrow return not found" << endl;
    }
}

BorrowReturn BorrowReturnRepository::getBorrowReturnById(int borrowReturnId) {
    ifstream inFile(_borrowReturnFileName);
    if (!inFile.is_open()) {
        cerr << "Can't open file to read" << endl;
        return BorrowReturn();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, userIdStr, bookIdStr, borrowAtStr, returnAtStr, numOfDaysStr, status;
        int day, month, year, cnt = 0;
        getline(ss, idStr, '|');
        getline(ss, userIdStr, '|');
        getline(ss, bookIdStr, '|');
        getline(ss, borrowAtStr, '|');
        getline(ss, returnAtStr, '|');
        getline(ss, numOfDaysStr, '|');
        getline(ss, status, '|');

        int id = atoi(idStr.c_str());
        if (id == borrowReturnId) {
            int userId = atoi(userIdStr.c_str());
            int bookId = atoi(bookIdStr.c_str());
            for( int i = 0; i < borrowAtStr.length(); i++ ) {
                if ( borrowAtStr[i] == '-' && cnt == 0 ) {
                    day = atoi(borrowAtStr.substr(0, i).c_str());
                    cnt = i + 1;
                } else if ( borrowAtStr[i] == '-' && cnt != 0 ) {
                    month = atoi(borrowAtStr.substr(cnt, i).c_str());
                    year = atoi(borrowAtStr.substr(i+1, borrowAtStr.length()).c_str());
                }
            }
           cnt = 0;
           Date borrowAt = Date(day, month, year);
           for( int i = 0; i < returnAtStr.length(); i++ ) {
               if ( returnAtStr[i] == '-' && cnt == 0 ) {
                   day = atoi(returnAtStr.substr(0, i).c_str());
                   cnt = i + 1;
               } else if ( returnAtStr[i] == '-' && cnt != 0 ) {
                   month = atoi(returnAtStr.substr(cnt, i).c_str());
                   year = atoi(returnAtStr.substr(i+1, returnAtStr.length()).c_str());
               }
           }
           cnt = 0;
           Date returnAt = Date(day, month, year);
           int numOfDays = atoi(numOfDaysStr.c_str());
           if ( status == "BORROWING" ) {
               return BorrowReturn(id, userId, bookId, borrowAt, returnAt, numOfDays, Status::BORROWING);
           } else {
               return BorrowReturn(id, userId, bookId, borrowAt, returnAt, numOfDays, Status::RETURNED);
           }
        }
    }

    inFile.close();
    cout << "Borrow return not found" << endl;
    return BorrowReturn();
}

List<BorrowReturn> BorrowReturnRepository::getAllBorrowReturns() {
    ifstream inFile(_borrowReturnFileName);
    List<BorrowReturn> borrowReturnList;
    if (!inFile.is_open()) {
        cerr << "Can't open file to read" << endl;
        return borrowReturnList;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, userIdStr, bookIdStr, borrowAtStr, returnAtStr, numOfDaysStr, status;
        int day, month, year, cnt = 0;

        getline(ss, idStr, '|');
        getline(ss, userIdStr, '|');
        getline(ss, bookIdStr, '|');
        getline(ss, borrowAtStr, '|');
        getline(ss, returnAtStr, '|');
        getline(ss, numOfDaysStr, '|');
        getline(ss, status, '|');

        int id = atoi(idStr.c_str());
        int userId = atoi(userIdStr.c_str());
        int bookId = atoi(bookIdStr.c_str());
        for( int i = 0; i < borrowAtStr.length(); i++ ) {
            if ( borrowAtStr[i] == '-' && cnt == 0 ) {
                day = atoi(borrowAtStr.substr(0, i).c_str());
                cnt = i + 1;
            } else if ( borrowAtStr[i] == '-' && cnt != 0 ) {
                month = atoi(borrowAtStr.substr(cnt, i).c_str());
                year = atoi(borrowAtStr.substr(i+1, borrowAtStr.length()).c_str());
            }
        }
        cnt = 0;
        Date borrowAt = Date(day, month, year);
        for( int i = 0; i < returnAtStr.length(); i++ ) {
            if ( returnAtStr[i] == '-' && cnt == 0 ) {
                day = atoi(returnAtStr.substr(0, i).c_str());
                cnt = i + 1;
            } else if ( returnAtStr[i] == '-' && cnt != 0 ) {
                month = atoi(returnAtStr.substr(cnt, i).c_str());
                year = atoi(returnAtStr.substr(i+1, returnAtStr.length()).c_str());
            }
        }
        cnt = 0;
        Date returnAt = Date(day, month, year);
        int numOfDays = atoi(numOfDaysStr.c_str());
        if ( status == "BORROWING" ) {
            borrowReturnList.InsertLast(BorrowReturn(id, userId, bookId, borrowAt, returnAt, numOfDays, Status::BORROWING));
        } else {
            borrowReturnList.InsertLast(BorrowReturn(id, userId, bookId, borrowAt, returnAt, numOfDays, Status::RETURNED));
        }
    }
    inFile.close();
    return borrowReturnList;
}

