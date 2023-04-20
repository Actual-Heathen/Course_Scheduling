#ifndef ENGINE_H
#define ENGINE_H

#endif // ENGINE_H

#include "../header/department.h"
#include "../header/sanitizer.h"
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct outputStruct {
    int conflictCount = 0;
    vector<Course> courseList;
};

bool compareInstructorPriority(Instructor& left, Instructor& right);
bool compareCourseType(Course& left, Course& right);

outputStruct generateSchedule(vector<Department> departments, map<string, RoomInfo> masterRooms);
outputStruct validateSchedule(vector<Course> courses, bool useRoomMap);
