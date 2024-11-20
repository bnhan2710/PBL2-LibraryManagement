#ifndef BORROW_RETURN_REPOSITORY_H
#define BORROW_RETURN_REPOSITORY_H

#include "BorrowReturn.h"
#include "../utils/List.h"

class BorrowReturnRepository {
private:
    static BorrowReturnRepository* _borrowReturnRepository; 
    static const char* _borrowReturnFileName;               
    static const char* _borrowReturnTempFileName;           
    List<BorrowReturn> _borrowReturnList;                                                    
    BorrowReturnRepository();                               
                                    

public:
    static BorrowReturnRepository* initBorrowReturnRepository(); 
    ~BorrowReturnRepository();

    void addBorrowReturn(const BorrowReturn& borrowReturn); 
    void updateBorrowReturn(const BorrowReturn& borrowReturn); 
    void deleteBorrowReturn(int borrowReturnId);           
    List<BorrowReturn> getAllBorrowReturns();              
    BorrowReturn getBorrowReturnById(int borrowReturnId);   
};

#endif 
