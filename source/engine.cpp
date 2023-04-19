#include "../header/engine.h"

using namespace std;

map<string, RoomInfo> masterRooms;

bool compareInstructorPriority(Instructor& left, Instructor& right)
{
    return left.getPriority() > right.getPriority();
}

//compare courses in T, S, A section type order
//test this, may be backwards
bool compareCourseType(Course& left, Course& right)
{
    return left.getSectionType() > right.getSectionType();
}

outputStruct generateSchedule(vector<Department> departments, map<string, RoomInfo> roomMap)
{
    masterRooms = roomMap;
    
    // functionality

    //for each department
    //      sort instructors by priority
    //      sort courses by section type
    //      assign instructors to prefered courses and times
    //      fill rest of courses with instructors/times
    //      assign rooms to courses

    for (Department department : departments)
    {
        //sort by instructor priority
        sort(department.instructorList.begin(), department.instructorList.end(), &compareInstructorPriority);
        //sort courses by section type in order T, S, A
        sort(department.courseList.begin(), department.courseList.end(), &compareCourseType);
    
        //assign instructors to preferred course
        for (Instructor instructor : department.instructorList)
        {
            string preferredCourse = instructor.getPreferredClass();
            if (instructor.getCurrentlyTeaching() < instructor.getMaxCourses())
            {
                for (Course course : department.courseList)
                {
                    if (course.getCourseNumber() == preferredCourse)
                    {
                        if (course.getSectionType() == 'A')
                        {
                            instructor.increaseClassesTaught();
                            course.setFirstName(instructor.getFirstName());
                            course.setLastName(instructor.getLastName());
                        }
                        else
                        {
                            int day;
                            int time;
                            instructor.getNextAvailability(&day, &time);
                            if (day != -1 && time != -1)
                            {
                                instructor.increaseClassesTaught();
                                course.setFirstName(instructor.getFirstName());
                                course.setLastName(instructor.getLastName());
                                instructor.setAvailability(day, time, 0);
                                course.setDay(day);
                                course.setTime(time);
                            }
                        }
                    }
                }
            }
        }

        //assign instructors to the rest of the courses
        int instructorIndex = 0;
        for (Course course : department.courseList)
        {
            if (course.getFirstName() == "TBA")
            {
                Instructor instructor;
                int previousIndex = instructorIndex;
                do {
                    instructor = department.instructorList.at(instructorIndex);
                    instructorIndex = (instructorIndex+1)%department.instructorList.size();
                } while (instructorIndex != previousIndex && instructor.getMaxCourses() <= instructor.getCurrentlyTeaching());
                if (instructor.getFirstName() != "TBA") //if instructor available
                {
                    if (course.getSectionType() == 'A')
                    {
                        department.instructorList.at(instructorIndex).increaseClassesTaught();
                        course.setFirstName(instructor.getFirstName());
                        course.setLastName(instructor.getLastName());
                    }
                    else  //add function that does this to Instructor
                    {
                        int day;
                        int time;
                        instructor.getNextAvailability(&day, &time);
                        if (day != -1 && time != -1)
                        {
                            department.instructorList.at(instructorIndex).increaseClassesTaught();
                            course.setFirstName(instructor.getFirstName());
                            course.setLastName(instructor.getLastName());
                            department.instructorList.at(instructorIndex).setAvailability(day, time, 0);
                            course.setDay(day);
                            course.setTime(time);
                        }                    
                    }
                }
            }
        }

        //assign rooms to the rest of the courses
        int roomIndex = 0;
        for (int courseIndex = 0; courseIndex < department.courseList.size(); courseIndex++)
        {
            Course course = department.courseList.at(courseIndex); //this is a temporary, local value for convenience. Do not update this variable. Instead update department.courseList.at(courseIndex)
            if (course.getSectionType() == 'T') //only set rooms to in person classes
            {
                string roomName = "";
                int previousRoom = roomIndex;
                do {
                    roomName = department.roomList.at(roomIndex);
                    roomIndex = (roomIndex+1)%department.roomList.size();
                } while (roomIndex != previousRoom && masterRooms[roomName].getAvailability(course.getDay(), course.getTime()) == 0);

                if (roomName != "") //if room available
                {
                    department.courseList.at(courseIndex).setRoom(roomName);
                    masterRooms[roomName].setAvailability(course.getDay(), course.getTime(), 0);
                }                
            }
        } 
    }

    vector<Course> courses;
    // make a master course list to pass into validateSchedule()
    for (int i = 0; i < departments.size(); i++)
    {
        for (int j = 0; j < departments.at(i).courseList.size(); j++)
        {
            courses.push_back(departments.at(i).courseList.at(j));
        }
    }
    return validateSchedule(courses, true);
}

outputStruct validateSchedule(vector<Course> courses, bool useRoomMap)
{
    outputStruct output;
    for (int i = 0; i < courses.size(); i++)
    {
        bool individual = false;
        // check for individual course conflicts
        // output.conflictCount++; for each conflict

        //check each field is filled

        //if class is online and has a room assigned
        if (courses.at(i).getSectionType() != 'T' && courses.at(i).getRoom() != "TBA") //course needs room name field
        {
            individual = true;
            output.conflictCount++;
        }

        //if class is in person and has no room assigned
        if (courses.at(i).getSectionType() == 'T' && courses.at(i).getRoom() == "TBA")
        {
            individual = true;
            output.conflictCount++;
        }

        //if class is asynchronous and has a time assigned
        if (courses.at(i).getSectionType() == 'A' && (courses.at(i).getDay() != -1 || courses.at(i).getTime() != -1))
        {
            individual = true;
            output.conflictCount++;
        }

        //if class is not asynchronous and has no time assigned
        if (courses.at(i).getSectionType() != 'A' && (courses.at(i).getDay() == -1 && courses.at(i).getTime() == -1))
        {
            individual = true;
            output.conflictCount++;
        }

        //if room size smaller than class max size
        if (useRoomMap && masterRooms[courses.at(i).getRoom()].getCapacity() < courses.at(i).getMaxEnroll())
        {
            individual = true;
            output.conflictCount++;
        }

        //update course conflict flag
        if (individual && courses.at(i).getConflict() == NONE) //should be an unnecessary check, but just to be sure
        {
            courses.at(i).setConflict(INDIVIDUAL);
        }

        else if (individual && courses.at(i).getConflict() == MULTIPLE) //should be an unnecessary check, but just to be sure
        {
            courses.at(i).setConflict(BOTH);
        }

        for (int j = i+1; j < courses.size(); j++)
        {
            bool multiple = false;

            //same CRN
            if (courses.at(i).getCRN() == courses.at(j).getCRN())
            {
                multiple = true;
                output.conflictCount++;
            }

            if (courses.at(i).getDay() == courses.at(j).getDay() && courses.at(i).getTime() == courses.at(j).getTime())//date and time is same
            {
                if (courses.at(i).getFirstName() == courses.at(j).getFirstName() && courses.at(i).getLastName() == courses.at(j).getLastName())//if time and instructor is the same
                {
                    multiple = true;
                    output.conflictCount++;
                }
                if (courses.at(i).getRoom() == courses.at(j).getRoom()) // if time and room is the same for both courses
                {
                    multiple = true;
                    output.conflictCount++;
                }
            }

            if (multiple)
            {
                if (courses.at(i).getConflict() == NONE) courses.at(i).setConflict(MULTIPLE);
                else if (courses.at(i).getConflict() == INDIVIDUAL) courses.at(i).setConflict(BOTH);

                if (courses.at(j).getConflict() == NONE) courses.at(j).setConflict(MULTIPLE);
                else if (courses.at(j).getConflict() == INDIVIDUAL) courses.at(j).setConflict(BOTH);
            }
        }
    }
    output.courseList = courses;
    return output;
}