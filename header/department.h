#pragma once
#include "course.h"
#include "instructor.h"
#include "room.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Department {
public:
    vector<Course> courseList;
    vector<Instructor> instructorList;
    vector<string> roomList;
    void sortInstructors();
    void sortCourses();
};
