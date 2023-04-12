#ifndef COURSE_H
#define COURSE_H

#endif // COURSE_H
#pragma once
#include "dayTime.h"
#include "instructor.h"
#include <string>
using namespace std;

class Course {
private:
	char sectionType = '0';
	int crn = 0;
	string courseNumber = "";
	string sectionNumber = "";
	string title = "";
	double credit = 0;
	int maxEnroll = 0;
	bool conflict = false;
	int day = -1;
	int time = -1;
	string instructorFirstName = "";
	string instructorLastName = "";
	string roomName = "";


public:
	void setSectionType(char input);
	void setCRN(int input);
	void setCourseNumber(string input);
	void setSectionNumber(string input);
	void setTitle(string input);
	void setCredit(double input);
	void setMaxEnroll(int input);
	void setConflict(bool input);
	void setDay(int day);
	void setTime(int time);
	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setRoom(string room);

	char getSectionType();
	int getCRN();
	string getCourseNumber();
	string getSectionNumber();
	string getTitle();
	double getCredit();
	int getMaxEnroll();
	bool getConflict();
	int getDay();
	int getTime();
	string getFirstName();
	string getLastName();
	string getRoom();
};
