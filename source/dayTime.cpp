#include "../headers/dayTime.h"
#include <iostream>

void DayTime::setOccupied(int days, int hours, bool status) {
	if (days != -1 && hours != -1) times[days][hours] = status;
}

bool DayTime::getOccupied(int days, int hours) {

	if (days != -1 && hours != -1) {
		return times[days][hours];
	}

	return true;
}