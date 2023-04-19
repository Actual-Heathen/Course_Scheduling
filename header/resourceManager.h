#pragma once

#include "../header/engine.h" //department include replaced with engine since engine include department
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int resourceManager(bool populated, int departmentCounter, string fileStoragePath);
int toOutput(outputStruct results);
int outToIn();
int validateSchedule();
Course createCourse(string data);
Instructor createInstructor(string data);
RoomInfo createRoom(string data);
