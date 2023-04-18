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

void Course::setConflict(bool input) {
    conflict = input;
}

void Course::setAvailability(int days, int hours, bool status) {
	schedule.setAvailability(days, hours, status);
}

void Course::setDay(int day)
{
	day = day;
}

void Course::setTime(int time)
{
    time = time;
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
    room = room;
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

bool Course::getAvailability(int days, int hours) {
	return schedule.getAvailability(days, hours);
}

int getDay()
{
	return day;
}

int getTime()
{
	return time;
}

string getFirstName()
{
	return instructorFirstName;
}

string getLastName()
{
	return instructorLastName;
}

string getRoom()
{
	return room;
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
