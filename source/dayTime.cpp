#include "../headers/dayTime.h"
#include <iostream>

int DayTime::stringToDays(string input) {
	int day = -1;

	input = stringToLower(input);

	if (stringToLower(input) == "mw") day = 0;
	if (stringToLower(input) == "tr") day = 1;

	return day;
}

int DayTime::stringToHour(string input) {
	int hour = -1;

	input = stringToLower(input);

	if (input == "8 am" || input == "8:00 am" || input == "08:00 am" || input == "8" || input == "8:00" || input == "08:00") hour = 0;
	if (input == "9:40 am" || input == "09:40 am" || input == "9:40" || input == "09:40") hour = 1;
	if (input == "11:20 am" || input == "11:20") hour = 2;
	if (input == "1 pm" || input == "1:00 pm" || input == "01:00 pm" || input == "13" || input == "13:00") hour = 3;
	if (input == "2:40 pm" || input == "02:40 pm" || input == "14:40") hour = 4;
	if (input == "4:20 pm" || input == "04:20 pm" || input == "16:20") hour = 5;

	return hour;
}

string DayTime::stringToLower(string input) {
	char* asChar = new char[input.length() + 1];

	asChar[input.length()] = '\0';

	for (int i = 0; i < input.length(); ++i) {
		asChar[i] = tolower(input[i]);
	}

	string stringLowercase = asChar;

	delete[] asChar;

	return stringLowercase;
}

void DayTime::setOccupied(string days, string hours, bool status) {
	int row, column;

	row = stringToDays(days);
	column = stringToHour(hours);

	if (row != -1 && column != -1) times[row][column] = status;
}

bool DayTime::getOccupied(string days, string hours) {
	int row, column;

	row = stringToDays(days);
	column = stringToHour(hours);

	if (row != -1 && column != -1) {
		return times[row][column];
	}

	return true;
}
