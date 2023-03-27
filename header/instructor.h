#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class Instructor {
private:
	string firstName;
	string lastName;
    int maxCourses;
	int priority;
	string preferredClass;
	bool conflict = false;
	DayTime schedule;

public:
	void setFirstName(string input);
	void setLastName(string input);
    void setMaxCourses(int input);
	void setPriority(int input);
	void setPreferredClass(string input);
    void setConflict(bool input);
    void setOccupied(int days, int hours, bool status);
    void setSchedule(DayTime input);
	string getFirstName();
	string getLastName();
    int getMaxCourses();
	int getPriority();
	string getPreferredClass();
	bool getConflict();
	bool getOccupied(int days, int hours);
    DayTime getSchedule();
};

