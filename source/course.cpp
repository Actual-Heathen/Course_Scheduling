#include "../header/course.h"

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

void Course::setConflict(CONFLICT input) {
	conflict = input;
}

void Course::setDay(int d)
{
	day = d;
}

void Course::setTime(int t)
{
	time = t;
}

void Course::setFirstName(string firstName)
{
	instructorFirstName = firstName;
}

void Course::setLastName(string lastName)
{
	instructorLastName = lastName;
}

void Course::setRoom(string room)
{
	roomName = room;
}

void Course:: setBuilding(string building)
{
	buildingName = building;
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

CONFLICT Course::getConflict() {
	return conflict;
}

int Course::getDay()
{
	return day;
}

int Course::getTime()
{
	return time;
}

string Course::getFirstName()
{
	return instructorFirstName;
}

string Course::getLastName()
{
	return instructorLastName;
}

string Course::getRoom()
{
	return roomName;
}

string Course::getBuilding()
{
	return buildingName;
}
