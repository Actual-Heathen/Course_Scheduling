#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class RoomInfo {
private:
	string buildingName;
	string roomNumber;
	int maxCapacity;
	bool conflict = false;
	DayTime schedule;

public:
	void setBuildingName(string input);
	void setRoomNumber(string input);
	void setCapacity(int input);
	void setConflict(bool input);
	void setOccupied(int days, int hours, bool status);
	string getBuildingName();
	string getRoomNumber();
	int getCapacity();
	bool getConflict();
	bool getOccupied(int days, int hours);
};

