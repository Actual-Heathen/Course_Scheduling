#pragma once

#include "../header/department.h"
#include <string>
#include <fstream>

using namespace std;

int resourceManager(bool populated, int departmentCounter, string fileStoragePath, string generatedSchedulePath);
Course createCourse(string data);
Instructor createInstructor(string data);
RoomInfo createRoom(string data);
