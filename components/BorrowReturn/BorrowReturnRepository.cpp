#include "BorrowReturnRepository.h"
#include <fstream>
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

void BorrowReturnRepository::addBorrowReturn( const BorrowReturn& borrowReturn) {
    ofstream outFile;
    outFile.open(_borrowReturnFileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Can't not open file to read and write" << endl;
        return;
    }

    outFile << borrowReturn.getId() << " "
            << borrowReturn.getUserId() << " "
            << borrowReturn.getBookId() << " "
            << borrowReturn.getBorrowAt().getDay() << " "
            << borrowReturn.getBorrowAt().getMonth() << " "
            << borrowReturn.getBorrowAt().getYear() << " "
            << borrowReturn.getReturnAt().getDay() << " "
            << borrowReturn.getReturnAt().getMonth() << " "
            << borrowReturn.getReturnAt().getYear() << " "
            << borrowReturn.getNumOfDays() << " "
            << borrowReturn.getStatus() << " "
            << endl;

    outFile.close();
    cout << "Borrow book successful" << endl;
}