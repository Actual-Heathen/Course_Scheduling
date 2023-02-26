#include "../headers/course.h"
#include "../headers/department.h"
#include "../headers/engine.h"
#include "../headers/instructor.h"
#include "../headers/resourceManager.h"
#include "../headers/room.h"

void DayTime::setOccupied(string days, string hours) {
	int row, column;

	row = stringToDays(days);
	column = stringToHour(hours);

	if (row != 666 && column != 666) times[row][column] = true;
}

bool DayTime::getOccupied(string days, string hours) {
	int row, column;

	row = stringToDays(days);
	column = stringToHour(hours);

	if (row != 666 && column != 666) return times[row][column];

	return 1;
}

int DayTime::stringToDays(string input) {
	int day = 666;

	if (input == "MW") day = 0;
	if (input == "TR") day = 1;

	return day;
}

int DayTime::stringToHour(string input) {
	int hour = 666;

	if (input == "8 AM" || input == "8:00 AM" || input == "08:00 AM" || input == "8:00" || input == "08:00") hour = 0;
	if (input == "9:40 AM" || input == "09:40 AM" || input == "9:40" || input == "09:40") hour = 1;
	if (input == "11:20 AM" || input == "11:20") hour = 2;
	if (input == "1 PM" || input == "1:00 PM" || input == "01:00 PM" || input == "13:00") hour = 3;
	if (input == "2.40 PM" || input == "02.40 PM" || input == "14.40") hour = 4;
	if (input == "4.20 PM" || input == "04.20 PM" || input == "16.20") hour = 5;

	return hour;
}

void Course::setSectionType(char input) {
	sectionType = input;
}

void Course::setCRN(int input) {
	crn = input;
}

void Course::setCourseNumber(string input) {
	courseNumber = input;
}

void Course::setSectionNumber(string input) {
	sectionNumber = input;
}

void Course::setTitle(string input) {
	title = input;
}

void Course::setCredit(double input) {
	credit = input;
}

void Course::setMaxEnroll(int input) {
	maxEnroll = input;
}

void Course::setConflict(bool input) {
	conflict = input;
}

void Course::setOccupied(string days, string hours) {
	schedule.setOccupied(days, hours);
}

char Course::getSectionType() {
	return sectionType;
}

int Course::getCRN() {
	return crn;
}

string Course::getCourseNumber() {
	return courseNumber;
}

string Course::getSectionNumber() {
	return sectionNumber;
}

string Course::getTitle() {
	return title;
}

double Course::getCredit() {
	return credit;
}

int Course::getMaxEnroll() {
	return maxEnroll;
}

bool Course::getConflict() {
	return conflict;
}

bool Course::getOccupied(string days, string hours) {
	return schedule.getOccupied(days, hours);
}

void RoomInfo::setBuildingName(string input) {
	buildingName = input;
}

void RoomInfo::setRoomNumber(string input) {
	roomNumber = input;
}

void RoomInfo::setOccupied(string days, string hours) {
	schedule.setOccupied(days, hours);
}

string RoomInfo::getBuildingName() {
	return buildingName;
}

string RoomInfo::getRoomNumber() {
	return roomNumber;
}

bool RoomInfo::getOccupied(string days, string hours) {
	schedule.setOccupied(days, hours);
}

void Instructor::setName(string input) {
	instructor = input;
}

void Instructor::setConflict(bool input) {
	conflict = input;
}

void Instructor::setOccupied(string days, string hours) {
	schedule.setOccupied(days, hours);
}

string Instructor::getName() {
	return instructor;
}

bool Instructor::getConflict() {
	return conflict;
}

bool Instructor::getOccupied(string days, string hours) {
	schedule.setOccupied(days, hours);
}
