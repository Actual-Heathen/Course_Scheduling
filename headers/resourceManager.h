#pragma once
#include <string>
using namespace std;

class DayTime {
private:
	bool times[2][6] = { {false, false, false, false, false, false}, {false, false, false, false, false, false} };
	int stringToDays(string input);
	int stringToHour(string input);

public:
	void setOccupied(string days, string hours);
	bool getOccupied(string days, string hours);
};

class Course {
private:
	char sectionType = 'ß';
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
	void setOccupied(string days, string hours);
	char getSectionType();
	int getCRN();
	string getCourseNumber();
	string getSectionNumber();
	string getTitle();
	double getCredit();
	int getMaxEnroll();
	bool getConflict();
	bool getOccupied(string days, string hours);
};

class RoomInfo {
private:
	string buildingName;
	string roomNumber;
	DayTime schedule;

public:
	void setBuildingName(string input);
	void setRoomNumber(string input);
	void setOccupied(string days, string hours);
	string getBuildingName();
	string getRoomNumber();
	bool getOccupied(string days, string hours);
};

class Instructor {
private:
	string instructor;
	bool conflict = false;
	DayTime schedule;

public:
	void setName(string input);
	void setConflict(bool input);
	void setOccupied(string days, string hours);
	string getName();
	bool getConflict();
	bool getOccupied(string days, string hours);
};