#include "../header/instructor.h"

void Instructor::setFirstName(string input) {
	firstName = input;
}

void Instructor::setLastName(string input) {
	lastName = input;
}

void Instructor::setPriority(int input) {
	priority = input;
}

void Instructor::setPreferredClass(string input) {
	preferredClass = input;
}

void Instructor::setConflict(bool input) {
	conflict = input;
}

void Instructor::setOccupied(int days, int hours, bool status) {
	schedule.setOccupied(days, hours, status);
}

string Instructor::getFirstName() {
	return firstName;
}

string Instructor::getLastName() {
	return lastName;
}

int Instructor::getPriority() {
	return priority;
}

string Instructor::getPreferredClass() {
	return preferredClass;
}

bool Instructor::getConflict() {
	return conflict;
}

bool Instructor::getOccupied(int days, int hours) {
	return schedule.getOccupied(days, hours);
}
