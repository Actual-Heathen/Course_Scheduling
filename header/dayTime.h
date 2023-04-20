#pragma once
#include <string>
using namespace std;

class DayTime {
public:
    static const int days = 2;
    static const int hours = 7;
    void setAvailability(int days, int hours, int status);
    int getAvailability(int days, int hours);

private:
    int times[days][hours] = { {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };
};
