#include "../headers/room.h"

void RoomInfo::setBuildingName(string input) {
	buildingName = input;
}

void RoomInfo::setRoomNumber(string input) {
	roomNumber = input;
}

void RoomInfo::setOccupied(string days, string hours, bool status) {
	schedule.setOccupied(days, hours, status);
}

string RoomInfo::getBuildingName() {
	return buildingName;
}

string RoomInfo::getRoomNumber() {
	return roomNumber;
}

bool RoomInfo::getOccupied(string days, string hours) {
	return schedule.getOccupied(days, hours);
}
