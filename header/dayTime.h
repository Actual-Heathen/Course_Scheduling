#pragma once
#include <string>
using namespace std;

class DayTime {
private:
    int times[2][7] = { {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };

public:
	void setOccupied(int days, int hours, int status);
	bool getOccupied(int days, int hours);
};
