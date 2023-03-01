#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class Instructor {
private:
	string instructor;
	bool conflict = false;
	DayTime schedule;

public:
	void setName(string input);
	void setConflict(bool input);
	void setOccupied(string days, string hours, bool status);
	string getName();
	bool getConflict();
	bool getOccupied(string days, string hours);
};
