#include "../header/room.h"

void RoomInfo::setBuildingName(string input) {
    buildingName = input;
}

void RoomInfo::setRoomNumber(string input) {
    roomNumber = input;
}

void RoomInfo::setCapacity(int input) {
    maxCapacity = input;
}

void RoomInfo::setConflict(bool input) {
    conflict = input;
}

void RoomInfo::setAvailability(int days, int hours, bool status) {
    schedule.setAvailability(days, hours, status);
}

string RoomInfo::getBuildingName() {
    return buildingName;
}

string RoomInfo::getRoomNumber() {
    return roomNumber;
}

int RoomInfo::getCapacity() {
    return maxCapacity;
}

bool RoomInfo::getConflict() {
    return conflict;
}

bool RoomInfo::getAvailability(int days, int hours) {
    return schedule.getAvailability(days, hours);
}
