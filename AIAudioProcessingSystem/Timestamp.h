#pragma once
#include <ostream>

class Timestamp {
private:
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

public:
    Timestamp();
    Timestamp(int h, int m, int s, int ms);

    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    int getMilliseconds() const;

    void setHours(int h);
    void setMinutes(int m);
    void setSeconds(int s);
    void setMilliseconds(int ms);

    long long getTotalMilliseconds() const;

    bool operator<(const Timestamp& other) const;

    bool operator==(const Timestamp& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Timestamp& ts);
};