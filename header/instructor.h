
#pragma once
#include "../header/dayTime.h"
#include <string>
using namespace std;

class Instructor {
private:
	string firstName = "TBA";
	string lastName = "TBA";
    int maxCourses = 0;
	int currentlyTeaching = 0;
	int priority = 0;
	int preferredCRN;
	DayTime schedule;

public:
	void setFirstName(string input);
	void setLastName(string input);
    void setMaxCourses(int input);
    void increaseClassesTaught();
    void decreaseClassesTaught();
	void setPriority(int input);
	void setPreferredCRN(int input);
    void setAvailability(int days, int hours, int status);
	string getFirstName();
	string getLastName();
    int getMaxCourses();
	int getCurrentlyTeaching();
	int getPriority();
	int getPreferredCRN();
	int getAvailability(int days, int hours);
    void getNextAvailability(int* day, int* time);
};
