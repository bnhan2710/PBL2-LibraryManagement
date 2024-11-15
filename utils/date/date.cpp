#include "date.h"

Date::Date(){
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

Date::Date(int d, int m, int y){
    this->day = d;
    this->month = m;
    this->year = y;
}
Date::~Date(){

}

void Date::setDay(int d){
    this->day = d;
}

void Date::setMonth(int m){
    this->month = m;
}

void Date::setYear(int y){
    this->year = y;
}

int Date::getDay(){
    return this->day;
}

int Date::getMonth(){
    return this->month;
}

int Date::getYear(){
    return this->year;
}

bool Date::isLeapYear(int year){
    if(year % 4 == 0){
        if(year % 100 == 0){
            if(year % 400 == 0){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

int Date::monthDays(){
    if(this->month == 2){
        if(isLeapYear(this->year)){
            return 29;
        }
        return 28;
    }
    if(this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11){
        return 30;
    }
    return 31;
}

void Date::nextDay(){
    if(this->day == monthDays()){
        this->day = 1;
        if(this->month == 12){
            this->month = 1;
            this->year++;
        }
        else{
            this->month++;
        }
    }
    else{
        this->day++;
    }
}


void Date::printDate(){
    cout << this->day << "/" << this->month << "/" << this->year << endl;
}

