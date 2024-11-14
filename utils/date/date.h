#pragma once
#include <iostream>
using namespace std;
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);
    ~Date();
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    int getDay();
    int getMonth();
    int getYear();
    bool isLeapYear(int);
    int monthDays();
    void nextDay();
    void printDate();   
};