#include "../header/engine.h"

using namespace std;

map<string, RoomInfo> masterRooms;

/*
Generates the schedule given a list of departments and map of room objects
for each department
    sort instructors by priority
    sort courses by section type
    assign instructors to preferred courses and times (if applicable)
    fill rest of courses with instructors/times wherever possible
    assign rooms to courses (if applicable)
*/
outputStruct generateSchedule(vector<Department> departments, map<string, RoomInfo> roomMap)
{
    masterRooms = roomMap; //save local Engine-class-level copy of rooms map for validation

    for (int deptIndex = 0; deptIndex < departments.size(); deptIndex++)
    {
        departments.at(deptIndex).sortInstructors(); //sort by instructor priority        
        departments.at(deptIndex).sortCoursesByType(); //sort courses by section type in order T, S, A

        //assign instructors to preferred course
        for (int instrIndex = 0; instrIndex < departments.at(deptIndex).instructorList.size(); instrIndex++)
        {
            int preferredCRN = departments.at(deptIndex).instructorList.at(instrIndex).getPreferredCRN(); //retrieve current instructor's desired CRN
            if (departments.at(deptIndex).instructorList.at(instrIndex).getCurrentlyTeaching() < departments.at(deptIndex).instructorList.at(instrIndex).getMaxCourses()) //if professor is not currently teaching at their max capacity
            {
                for (int courseIndex = 0; courseIndex < departments.at(deptIndex).courseList.size(); courseIndex++)
                {
                    if (departments.at(deptIndex).courseList.at(courseIndex).getCRN() == preferredCRN) //find course matching instructor's desired CRN
                    {
                        if (departments.at(deptIndex).courseList.at(courseIndex).getSectionType() == 'A') //asychronous courses do not require a time to be set, so set the professor to the course and increase the number of classes the instructor is teaching
                        {
                            departments.at(deptIndex).instructorList.at(instrIndex).increaseClassesTaught();
                            departments.at(deptIndex).courseList.at(courseIndex).setFirstName(departments.at(deptIndex).instructorList.at(instrIndex).getFirstName());
                            departments.at(deptIndex).courseList.at(courseIndex).setLastName(departments.at(deptIndex).instructorList.at(instrIndex).getLastName());
                        }
                        else if (departments.at(deptIndex).courseList.at(courseIndex).getSectionType() == 'S' || departments.at(deptIndex).courseList.at(courseIndex).getSectionType() == 'T') //if class is sychronous or traditional (in-person), a time must be found
                        {
                            int day;
                            int time;
                            departments.at(deptIndex).instructorList.at(instrIndex).getNextAvailability(&day, &time); //populates day and time with the first available time (by priority) the instructor is available
                            if (day != -1 && time != -1) //if the professor is available, set the day and time to the course, set the instructor as unavailable at day and time, set professor to the course, and increase instructor courses taught
                            {
                                departments.at(deptIndex).instructorList.at(instrIndex).increaseClassesTaught();
                                departments.at(deptIndex).courseList.at(courseIndex).setFirstName(departments.at(deptIndex).instructorList.at(instrIndex).getFirstName());
                                departments.at(deptIndex).courseList.at(courseIndex).setLastName(departments.at(deptIndex).instructorList.at(instrIndex).getLastName());
                                departments.at(deptIndex).instructorList.at(instrIndex).setAvailability(day, time, 0);
                                departments.at(deptIndex).courseList.at(courseIndex).setDay(day);
                                departments.at(deptIndex).courseList.at(courseIndex).setTime(time);
                            }
                        }
                    }
                }
            }
        }

        //assign instructors to the rest of the courses
        int instructorIndex = 0;
        for (int courseIndex = 0; courseIndex < departments.at(deptIndex).courseList.size(); courseIndex++)
        {
            if (departments.at(deptIndex).courseList.at(courseIndex).getFirstName() == "TBA")
            {
                int previousIndex = instructorIndex;
                do {
                    instructorIndex = (instructorIndex+1)%departments.at(deptIndex).instructorList.size(); //used to loop through instructors so each is only checked once, and so the first professors in the list are not automatically assigned each class until they are unavailable; evenly distributes courses to instructors
                    if (departments.at(deptIndex).instructorList.at(instructorIndex).getMaxCourses() > departments.at(deptIndex).instructorList.at(instructorIndex).getCurrentlyTeaching()) //if instructor available to teach another class
                    {
                        if (departments.at(deptIndex).courseList.at(courseIndex).getSectionType() == 'A')//asychronous courses do not require a time to be set, so set the professor to the course and increase the number of classes the instructor is teaching
                        {
                            departments.at(deptIndex).instructorList.at(instructorIndex).increaseClassesTaught();
                            departments.at(deptIndex).courseList.at(courseIndex).setFirstName(departments.at(deptIndex).instructorList.at(instructorIndex).getFirstName());
                            departments.at(deptIndex).courseList.at(courseIndex).setLastName(departments.at(deptIndex).instructorList.at(instructorIndex).getLastName());
                            break;
                        }
                        else if (departments.at(deptIndex).courseList.at(courseIndex).getSectionType() == 'S' || departments.at(deptIndex).courseList.at(courseIndex).getSectionType() == 'T')
                        {
                            int day;
                            int time;
                            departments.at(deptIndex).instructorList.at(instructorIndex).getNextAvailability(&day, &time);//populates day and time with the first available time (by priority) the instructor is available
                            if (day != -1 && time != -1) //if the professor is available, set the day and time to the course, set the instructor as unavailable at day and time, set professor to the course, and increase instructor courses taught
                            {
                                departments.at(deptIndex).instructorList.at(instructorIndex).increaseClassesTaught();
                                departments.at(deptIndex).courseList.at(courseIndex).setFirstName(departments.at(deptIndex).instructorList.at(instructorIndex).getFirstName());
                                departments.at(deptIndex).courseList.at(courseIndex).setLastName(departments.at(deptIndex).instructorList.at(instructorIndex).getLastName());
                                departments.at(deptIndex).instructorList.at(instructorIndex).setAvailability(day, time, 0);
                                departments.at(deptIndex).courseList.at(courseIndex).setDay(day);
                                departments.at(deptIndex).courseList.at(courseIndex).setTime(time);
                                break;
                            }
                        }
                    }
                } while (instructorIndex != previousIndex); //if an instructor cannot be assigned, their information for the course will be the default "TBA" and will appear as a conflict           
            }
        }

        //assign rooms to the rest of the courses
        int roomIndex = 0;
        for (int courseIndex = 0; courseIndex < departments.at(deptIndex).courseList.size(); courseIndex++)
        {
            Course course = departments.at(deptIndex).courseList.at(courseIndex); //this is a temporary, local value for convenience. Do not update this variable. Instead update department.courseList.at(courseIndex)
            if (course.getSectionType() == 'T' && course.getDay() != -1 && course.getTime() != -1) //only set rooms to in person classes with assigned time
            {
                string roomName = "";
                int previousRoom = roomIndex;
                do {
                    roomName = departments.at(deptIndex).roomList.at(roomIndex);
                    roomIndex = (roomIndex+1)%departments.at(deptIndex).roomList.size(); //used to evenly distribute courses across all available rooms
                    if (masterRooms[roomName].getCapacity() >= course.getMaxEnroll() && masterRooms[roomName].getAvailability(course.getDay(), course.getTime()) == 1) //if room available and large enough for this course's max enrollment
                    {
                        departments.at(deptIndex).courseList.at(courseIndex).setRoom(roomName);
                        masterRooms[roomName].setAvailability(course.getDay(), course.getTime(), 0);
                        break;
                    }
                } while (roomIndex != previousRoom);
            }
        }
    }

    vector<Course> courses;
    // make a master course list to pass into validateSchedule()
    for (int i = 0; i < departments.size(); i++)
    {
        for (int j = 0; j < departments.at(i).courseList.size(); j++)
        {
            Course course = departments.at(i).courseList.at(j);
            string newTitle = departments.at(i).getName() + " " + course.getCourseNumber();
            course.setCourseNumber(newTitle); //add department name to course name for displaying to user
            courses.push_back(course);
        }
    }
    sort(courses.begin(), courses.end(), [](Course& lhs, Course& rhs) { //sort courses list by course name
        return lhs.getCourseNumber() < rhs.getCourseNumber();
    });
    return validateSchedule(courses, true);
}

/*
validateSchedule sets the conflict flags and updates a conflict counter 
wherever conflicts between classes or an invalid field is present

Returns struct containing the completed list of courses and an integer conflict counter

useRoomMap determines whether or not the size of the course will be compared against the size of the room
this is set to true after generating a schedule since the room map is available, 
and false when the user opts to validate their modified schedule since the room map is no longer available
*/
outputStruct validateSchedule(vector<Course> courses, bool useRoomMap)
{
    outputStruct output;
    for (int i = 0; i < courses.size(); i++)
    {
        bool individual = false;
        // check for individual course conflicts
        // output.conflictCount++; for each conflict

        //check each field is filled

        //section type
        if (!Sanitizer::isValidSectionType(courses.at(i))) //must be 'A', 'S', or 'T'
        {
            individual = true;
            output.conflictCount++;
        }

        //CRN
        if (courses.at(i).getCRN() <= 0)
        {
            individual = true;
            output.conflictCount++;
        }

        //course number
        if (courses.at(i).getCourseNumber() == "-1")
        {
            individual = true;
            output.conflictCount++;
        }

        //section number
        if (courses.at(i).getSectionNumber() == "-1")
        {
            individual = true;
            output.conflictCount++;
        }

        //title
        if (courses.at(i).getTitle() == "TBA")
        {
            individual = true;
            output.conflictCount++;
        }

        //credit
        if (courses.at(i).getCredit() < 0 )
        {
            individual = true;
            output.conflictCount++;
        }

        //max enroll
        if (courses.at(i).getMaxEnroll() <= 0)
        {
            individual = true;
            output.conflictCount++;
        }

        //instructor
        if (courses.at(i).getFirstName() == "TBA" || courses.at(i).getLastName() == "TBA")
        {
            individual = true;
            output.conflictCount++;
        }

        //if class is online and has a room assigned
        if (courses.at(i).getSectionType() != 'T' && courses.at(i).getRoom() != "TBA")
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
        if (courses.at(i).getSectionType() != 'A' && (courses.at(i).getDay() == -1 || courses.at(i).getTime() == -1))
        {
            individual = true;
            output.conflictCount++;
        }

        //if room size smaller than class max size
        if (useRoomMap && courses.at(i).getRoom() != "TBA" && masterRooms[courses.at(i).getRoom()].getCapacity() < courses.at(i).getMaxEnroll())
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

        for (int j = i+1; j < courses.size(); j++) //check course i against all courses to the right of it in the course list
        {
            bool multiple = false;

            //same CRN
            if (courses.at(i).getCRN() == courses.at(j).getCRN())
            {
                multiple = true;
                output.conflictCount++;
            }

            if (courses.at(i).getDay() != -1 && courses.at(i).getTime() != -1 && courses.at(i).getDay() == courses.at(j).getDay() && courses.at(i).getTime() == courses.at(j).getTime())//date and time is same
            {
                if (courses.at(i).getFirstName() != "TBA" && courses.at(i).getFirstName() == courses.at(j).getFirstName() && courses.at(i).getLastName() == courses.at(j).getLastName())//if time and instructor is the same
                {
                    multiple = true;
                    output.conflictCount++;
                }
                if (courses.at(i).getRoom() != "TBA" && courses.at(i).getRoom() == courses.at(j).getRoom()) // if time and room is the same for both courses
                {
                    multiple = true;
                    output.conflictCount++;
                }
            }

            //update conflict type if conflicts occurred between courses i and j
            if (multiple)
            {
                if (courses.at(i).getConflict() == NONE) courses.at(i).setConflict(MULTIPLE);
                else if (courses.at(i).getConflict() == INDIVIDUAL) courses.at(i).setConflict(BOTH);

                if (courses.at(j).getConflict() == NONE) courses.at(j).setConflict(MULTIPLE);
                else if (courses.at(j).getConflict() == INDIVIDUAL) courses.at(j).setConflict(BOTH);
            }
        }
    }
    output.courseList = courses; //update output structure
    return output;
}
