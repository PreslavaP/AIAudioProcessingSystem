#include "Timestamp.h"
#include <iomanip>

Timestamp::Timestamp() : hours(0), minutes(0), seconds(0), milliseconds(0) {}

Timestamp::Timestamp(int h, int m, int s, int ms) {
	setHours(h);
	setMinutes(m);
	setSeconds(s);
	setMilliseconds(ms);
}

int Timestamp::getHours() const { return hours; }
int Timestamp::getMinutes() const { return minutes; }
int Timestamp::getSeconds() const { return seconds; }
int Timestamp::getMilliseconds() const { return milliseconds; }


//Проверка за коректност на времето
void Timestamp::setHours(int h) {
	if (h >= 0 && h <= 23) {
		hours = h;
	}
	else {
		hours = 0;
	}
}

void Timestamp::setMinutes(int m) {
	if (m >= 0 && m <= 59) {
		minutes = m;
	}
	else {
		minutes = 0;
	}
}

void Timestamp::setSeconds(int s) {
	if (s >= 0 && s <= 59) {
		seconds = s;
	}
	else {
		seconds = 0;
	}
}

void Timestamp::setMilliseconds(int ms) {
	if (ms >= 0 && ms <= 999) {
		milliseconds = ms;
	}
	else {
		milliseconds = 0;
	}
}

//Превръща цялото време в общо милисекунди
long long Timestamp::getTotalMilliseconds() const {
	return (static_cast<long long>(hours) * 3600000) +
		(static_cast<long long>(minutes) * 60000) +
		(static_cast<long long>(seconds) * 1000) +
		milliseconds;
}

//Оператор за сравнение
bool Timestamp::operator<(const Timestamp& other) const {
	return this->getTotalMilliseconds() < other.getTotalMilliseconds();
}

//Оператор за равенство
bool Timestamp::operator==(const Timestamp& other) const {
	return this->getTotalMilliseconds() == other.getTotalMilliseconds();
}

//Функция за печат в конзолата
std::ostream& operator<<(std::ostream& os, const Timestamp& ts) {
	os << std::setfill('0')
		<< std::setw(2) << ts.hours << ":"
		<< std::setw(2) << ts.minutes << ":"
		<< std::setw(2) << ts.seconds << "."
		<< std::setw(3) << ts.milliseconds;
	return os;
}