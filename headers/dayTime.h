#pragma once
#include <string>
using namespace std;

class DayTime {
private:
	bool times[2][6] = { {false, false, false, false, false, false}, {false, false, false, false, false, false} };

public:
	int stringToDays(string input);
	int stringToHour(string input);
	string stringToLower(string input);

	void setOccupied(string days, string hours, bool status);
	bool getOccupied(string days, string hours);
};