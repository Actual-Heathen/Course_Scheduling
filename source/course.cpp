#include "../headers/course.h"

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

void Course::setOccupied(int days, int hours, bool status) {
	schedule.setOccupied(days, hours, status);
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

bool Course::getOccupied(int days, int hours) {
	return schedule.getOccupied(days, hours);
}

