#pragma once

#include "../header/department.h"   // Used for Course, Instructor and RoomInfo structs
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int resourceManager(bool populated, int departmentCounter, string fileStoragePath);
int toOutput(vector<Course> courseList);
vector<Course> outToIn();
int validateSchedule();
Course createCourse(string data);
Instructor createInstructor(string data);
RoomInfo createRoom(string data);
