#pragma once

#include "../header/department.h"   // Used for Course, Instructor and RoomInfo structs
#include <string>
#include <fstream>

using namespace std;

int resourceManager(bool populated, int departmentCounter, string fileStoragePath);
int validateSchedule();
Course createCourse(string data);
Instructor createInstructor(string data);
RoomInfo createRoom(string data);
