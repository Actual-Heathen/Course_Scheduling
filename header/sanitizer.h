#pragma once
#include <string>
#include "../header/course.h"
using namespace std;

class Sanitizer
{
private:
    /* data */
public:
    static bool isValidDay(std::string s);
    static bool isValidTime(std::string s);
    static bool isInt(std::string s);
    static bool isValidSectionType(Course course);
};

