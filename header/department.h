#pragma once
#include "course.h"
#include "instructor.h"
#include "room.h"
#include <string>
#include <vector>
using namespace std;

class Department {
public:
	vector<Course> courseList;
	vector<Instructor> instructiorList;
	vector<RoomInfo> roomList;
};