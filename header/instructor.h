#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class Instructor {
private:
	string firstName;
	string lastName;
	int priority;
	string preferredClass;
	bool conflict = false;
	DayTime schedule;

public:
	void setFirstName(string input);
	void setLastName(string input);
	void setPriority(int input);
	void setPreferredClass(string input);
	void setConflict(bool input);
	void setOccupied(int days, int hours, bool status);
	string getFirstName();
	string getLastName();
	int getPriority();
	string getPreferredClass();
	bool getConflict();
	bool getOccupied(int days, int hours);
};
