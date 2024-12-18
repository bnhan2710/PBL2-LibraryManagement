#pragma once
#include <iostream>
#include <string>
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
    string getFormattedDate();
    bool isLeapYear(int);
    int monthDays();
    void nextDay();
    void printDate();   
};
