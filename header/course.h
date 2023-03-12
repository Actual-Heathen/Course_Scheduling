#ifndef COURSE_H
#define COURSE_H

#endif // COURSE_H
#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class Course {
private:
	char sectionType = ' ';
	int crn = 0;
	string courseNumber = "";
	string sectionNumber = "";
	string title = "";
	double credit = 0;
	int maxEnroll = 0;
	bool conflict = false;
	DayTime schedule;

public:
	void setSectionType(char input);
	void setCRN(int input);
	void setCourseNumber(string input);
	void setSectionNumber(string input);
	void setTitle(string input);
	void setCredit(double input);
	void setMaxEnroll(int input);
	void setConflict(bool input);
	void setOccupied(int days, int hours, bool status);
	char getSectionType();
	int getCRN();
	string getCourseNumber();
	string getSectionNumber();
	string getTitle();
	double getCredit();
	int getMaxEnroll();
	bool getConflict();
	bool getOccupied(int days, int hours);
};
