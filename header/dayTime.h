#pragma once
#include <string>
using namespace std;

class DayTime {
private:
    static const int days = 2;
    static const int hours = 7;
    int times[days][hours] = { {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };

public:
    void setAvailability(int days, int hours, int status);
    bool getAvailability(int days, int hours);
};
