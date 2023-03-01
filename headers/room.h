#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class RoomInfo {
private:
	string buildingName;
	string roomNumber;
	DayTime schedule;

public:
	void setBuildingName(string input);
	void setRoomNumber(string input);
	void setOccupied(string days, string hours, bool status);
	string getBuildingName();
	string getRoomNumber();
	bool getOccupied(string days, string hours);
};
