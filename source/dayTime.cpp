#include "../header/dayTime.h"
#include <iostream>

void DayTime::setAvailability(int days, int hours, int status) {
    if (days != -1 && hours != -1) times[days][hours] = status;
}

bool DayTime::getAvailability(int daysInput, int hoursInput) {
    if (daysInput != -1 && hoursInput != -1 && daysInput <= days && hoursInput <= hours) {
        return times[daysInput][hoursInput];
    }
    return 1;
}
