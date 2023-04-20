#include "../header/department.h"

void Department::sortInstructors()
{
    sort(instructorList.begin(), instructorList.end(), [](Instructor& lhs, Instructor& rhs) {
        return lhs.getPriority() > rhs.getPriority();
    });
}

void Department::sortCoursesByType()
{
    sort(courseList.begin(), courseList.end(), [](Course& lhs, Course& rhs) {
        return lhs.getSectionType() > rhs.getSectionType();
    });
}
