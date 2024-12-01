#include "BorrowReturnService.h"
BorrowReturnService* BorrowReturnService::_borrowReturnService = nullptr;

BorrowReturnService::BorrowReturnService() {
    this->_borrowReturnRepository = BorrowReturnRepository::initBorrowReturnRepository();
    this->_borrowReturnList = this->_borrowReturnRepository->getAllBorrowReturns();
}

BorrowReturnService::~BorrowReturnService() {
}

BorrowReturnService* BorrowReturnService::initBorrowReturnService() {
    if (_borrowReturnService == nullptr) {
        _borrowReturnService = new BorrowReturnService();
    }
    return _borrowReturnService;
}

void BorrowReturnService::BorrowBook(int userId, int bookId, int num_of_days, Date borrowAt, Date returnAt) {
    int borrowReturnId = this->_borrowReturnList.GetLength() + 1;
    BorrowReturn borrowReturn(borrowReturnId, userId, bookId, borrowAt, returnAt, num_of_days, Status::BORROWING);
    this->_borrowReturnList.InsertLast(borrowReturn);
    this->_borrowReturnRepository->addBorrowReturn(borrowReturn);
    cout << "Borrow book successful" << endl;
}

void BorrowReturnService::ReturnBook(int borrowReturnId) {
    BorrowReturn borrowReturn = this->_borrowReturnRepository->getBorrowReturnById(borrowReturnId);
    if (borrowReturn.getId() == 0) {
        cout << "Borrow return not found!" << endl;
        return;
    }
    borrowReturn.setStatus(Status::RETURNED);
    this->_borrowReturnRepository->updateBorrowReturn(borrowReturn);
    cout << "Return book successful" << endl;
}

void BorrowReturnService::updateBorrowReturn(const BorrowReturn& updatedBorrowReturn) {
    this->_borrowReturnRepository->updateBorrowReturn(updatedBorrowReturn);
    cout << "Borrow return updated successfully!" << endl;
}

void BorrowReturnService::deleteBorrowReturn(int borrowReturnId) {
    this->_borrowReturnRepository->deleteBorrowReturn(borrowReturnId);
    cout << "Borrow return deleted successfully!" << endl;
}

List<BorrowReturn> BorrowReturnService::getBorrowList() {
    return this->_borrowReturnRepository->getAllBorrowReturns();
}

List<BorrowReturn> BorrowReturnService::getBorrowList(int userId) {
    List<BorrowReturn> allBorrowList = this->_borrowReturnRepository->getAllBorrowReturns();
    List<BorrowReturn> borrowList;
    for (int i = 0; i < allBorrowList.GetLength(); i++) {
        if (allBorrowList[i].getUserId() == userId) {
            borrowList.InsertLast(allBorrowList[i]);
        }
    }
    return borrowList;
}

