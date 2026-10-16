#include "Date.h"
#include <iomanip>

// Проверка за високосна година
bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Връща броя дни в даден месец, съобразявайки се с високосните години
int Date::getDaysInMonth(int m, int y) const {
    switch (m) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
    case 4: case 6: case 9: case 11: return 30;
    case 2: return isLeapYear(y) ? 29 : 28;
    default: return 30;
    }
}

Date::Date() : year(2026), month(10), day(13) {}

Date::Date(int year, int month, int day) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }

void Date::setYear(int y) {
    if (y >= 1900 && y <= 2100) {
        year = y;
    }
    else {
        year = 2026;
    }
}

void Date::setMonth(int m) {
    if (m >= 1 && m <= 12) {
        month = m;
    }
    else {
        month = 1;
    }
}

void Date::setDay(int d) {
    if (d >= 1 && d <= getDaysInMonth(month, year)) {
        day = d;
    }
    else {
        day = 1;
    }
}

// Претоварване на оператора за извеждане с водещи нули (напр. 2026-10-05 вместо 2026-10-5)
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setfill('0')
        << std::setw(4) << date.year << "-"
        << std::setw(2) << date.month << "-"
        << std::setw(2) << date.day;
    return os;
}