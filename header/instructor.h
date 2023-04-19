#pragma once
#include "../header/dayTime.h"
#include <string>
using namespace std;

class Instructor {
private:
	string firstName;
	string lastName;
    int maxCourses = 0;
	int currentlyTeaching = 0;
	int priority = 0;
	string preferredClass;
	DayTime schedule;

public:
	void setFirstName(string input);
	void setLastName(string input);
    void setMaxCourses(int input);
    void increaseClassesTaught();
    void decreaseClassesTaught();
	void setPriority(int input);
	void setPreferredClass(string input);
    void setAvailability(int days, int hours, int status);
	string getFirstName();
	string getLastName();
    int getMaxCourses();
	int getCurrentlyTeaching();
	int getPriority();
	string getPreferredClass();
	int getAvailability(int days, int hours);
    void getNextAvailability(int* day, int* time);
};

