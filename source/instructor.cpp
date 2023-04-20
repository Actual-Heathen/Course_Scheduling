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

int Instructor::getAvailability(int days, int hours) {
	return schedule.getAvailability(days, hours);
}

void Instructor::getNextAvailability(int* day, int* time)
{
    //check for available preferred times
    for (int d = 0; d < schedule.days; d++)
    {
        for (int h = 0; h < schedule.hours; h++)
        {
            int availability = getAvailability(d,h);
            if (availability == 2)
            {
                *day = d;
                *time = h;
                return;
            }
        }
    }

    //check for any available times
    for (int d = 0; d < schedule.days; d++)
    {
        for (int h = 0; h < schedule.hours; h++)
        {
            int availability = getAvailability(d,h);
            if (availability == 1)
            {
                *day = d;
                *time = h;
                return;
            }
        }
    }

    //no times available, return "null"
    *day = -1;
    *time = -1;
}