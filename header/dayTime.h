#pragma once
#include <string>
using namespace std;

class DayTime {
private:
	bool times[2][7] = { {false, false, false, false, false, false, false}, {false, false, false, false, false, false, false} };

public:
	void setOccupied(int days, int hours, bool status);
	bool getOccupied(int days, int hours);
};