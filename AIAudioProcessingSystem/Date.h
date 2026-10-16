#pragma once
#include <ostream>

class Date {
private:
    int year;
    int month;
    int day;

    // Помощни методи за валидация
    bool isLeapYear(int y) const;
    int getDaysInMonth(int m, int y) const;

public:
    Date(); 
    Date(int year, int month, int day); 

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};