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

void RoomInfo::setOccupied(int days, int hours, bool status) {
	schedule.setOccupied(days, hours, status);
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

bool RoomInfo::getOccupied(int days, int hours) {
	return schedule.getOccupied(days, hours);
}
