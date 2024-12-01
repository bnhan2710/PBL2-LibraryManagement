#include "BorrowReturn.h"
#include "BorrowReturnRepository.h"
#include "../utils/List.h"
class BorrowReturnService {
private:
    BorrowReturnService();
    static BorrowReturnService* _borrowReturnService;
    BorrowReturnRepository* _borrowReturnRepository;
    List<BorrowReturn> _borrowReturnList;
public:
    static BorrowReturnService* initBorrowReturnService();
    ~BorrowReturnService();
    void BorrowBook(int userId, int bookId, int num_of_days, Date borrowAt , Date returnAt);
    void ReturnBook(int borrowReturnId);
    void updateBorrowReturn(const BorrowReturn& updatedBorrowReturn);
    void deleteBorrowReturn(int borrowReturnId);
    List<BorrowReturn> getBorrowList();
    List<BorrowReturn> getBorrowList(int userId);
};
    
