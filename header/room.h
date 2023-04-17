#pragma once
#include "dayTime.h"
#include <string>
using namespace std;

class RoomInfo {
private:
    string buildingName;
    string roomNumber;
    int maxCapacity = 0;
    bool conflict = false;
    DayTime schedule;

public:
    void setBuildingName(string input);
    void setRoomNumber(string input);
    void setCapacity(int input);
    void setConflict(bool input);
    void setAvailability(int days, int hours, bool status);
    string getBuildingName();
    string getRoomNumber();
    int getCapacity();
    bool getConflict();
    bool getAvailability(int days, int hours);
};
