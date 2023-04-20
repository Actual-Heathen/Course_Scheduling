#ifndef COURSE_H
#define COURSE_H

#endif // COURSE_H
#pragma once
#include "dayTime.h"
#include "instructor.h"
#include <string>
using namespace std;

enum CONFLICT {
    NONE = 0,
    INDIVIDUAL = 1,
    MULTIPLE = 2,
    BOTH = 3
};

class Course {
private:
    char sectionType = '0';
    int crn = 0;
    string courseNumber = "-1";
    string sectionNumber = "-1";
    string title = "TBA";
    double credit = -1;
    int maxEnroll = 0;
    CONFLICT conflict = NONE;
    int day = -1;
    int time = -1;
    string instructorFirstName = "TBA";
    string instructorLastName = "TBA";
    string roomName = "TBA";

public:
    void setSectionType(char input);
    void setCRN(int input);
    void setCourseNumber(string input);
    void setSectionNumber(string input);
    void setTitle(string input);
    void setCredit(double input);
    void setMaxEnroll(int input);
    void setConflict(CONFLICT input);
    void setDay(int d);
    void setTime(int t);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setRoom(string room); //room name is equal to building + " " + room in accordance with the master room list key format

    char getSectionType();
    int getCRN();
    string getCourseNumber();
    string getSectionNumber();
    string getTitle();
    double getCredit();
    int getMaxEnroll();
    CONFLICT getConflict();
    string conflictToString();
    int getDay();
    int getTime();
    string getFirstName();
    string getLastName();
    string getRoom();
};
