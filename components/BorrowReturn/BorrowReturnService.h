#include "BorrowReturn.h"
#include "BorrowReturnRepository.h"
#include "../utils/List.h"
enum Status {
    BORROWING,
    RETURNED
};
class BorrowReturnService {
private:
    BorrowReturnService();
    static BorrowReturnService* _borrowReturnService;
    BorrowReturnRepository* _borrowReturnRepository;
    List<BorrowReturn> _borrowReturnList;
public:
    static BorrowReturnService* initBorrowReturnService();
    ~BorrowReturnService();
    void BorrowBook(int id, int userId, int bookId, int num_of_days, Date borrowAt , Date returnAt);
    void ReturnBook(int borrowReturnId);
    void updateBorrowReturn(const BorrowReturn& updatedBorrowReturn);
    void deleteBorrowReturn(int borrowReturnId);
    List<BorrowReturn> getAllBorrowList();
    BorrowReturn getBorrowListByUserId(int userId);
};
    