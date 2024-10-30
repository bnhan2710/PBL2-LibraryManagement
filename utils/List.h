#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
template<typename T> class List;
template<typename T>
class List
{
    int length;
    T* data;
public:
    List();
    List(int);
    ~List();
    void Erase();
    T& operator[](int);
    int GetLength() const;
    void Reallocate(int);
    void Resize(int);
    void Insert(T, int);
    void Remove(int);
    void InsertFirst(T);
    void InsertLast(T);
};