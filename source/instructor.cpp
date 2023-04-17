#include "../header/instructor.h"

void Instructor::setFirstName(string input) {
    firstName = input;
}

void Instructor::setLastName(string input) {
    lastName = input;
}

void Instructor::setMaxCourses(int input) {
    maxCourses = input;
}

void Instructor::increaseClassesTaught() {
    ++currentlyTeaching;
}

void Instructor::decreaseClassesTaught() {
    --currentlyTeaching;
}

void Instructor::setPriority(int input) {
    priority = input;
}

void Instructor::setPreferredClass(string input) {
    preferredClass = input;
}

void Instructor::setAvailability(int days, int hours, int status) {
    schedule.setAvailability(days, hours, status);
}

string Instructor::getFirstName() {
    return firstName;
}

string Instructor::getLastName() {
    return lastName;
}

int Instructor::getMaxCourses() {
    return maxCourses;
}

int Instructor::getCurrentlyTeaching() {
    return currentlyTeaching;
}

int Instructor::getPriority() {
    return priority;
}

string Instructor::getPreferredClass() {
    return preferredClass;
}

bool Instructor::getAvailability(int days, int hours) {
    return schedule.getAvailability(days, hours);
}
