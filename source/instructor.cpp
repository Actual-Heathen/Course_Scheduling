#include "../headers/instructor.h"

void Instructor::setName(string input) {
	instructor = input;
}

void Instructor::setConflict(bool input) {
	conflict = input;
}

void Instructor::setOccupied(string days, string hours, bool status) {
	schedule.setOccupied(days, hours, status);
}

string Instructor::getName() {
	return instructor;
}

bool Instructor::getConflict() {
	return conflict;
}

bool Instructor::getOccupied(string days, string hours) {
	return schedule.getOccupied(days, hours);
}
