// This file is being used by Jeni to develop backend without conflicting with anyone else's work.
// It will be deleted once its functionality is able to be added directly into the backend.

#include <vector>

using namespace std;

enum CONFLICT {
    NONE = 0,
    INDIVIDUAL = 1,
    MULTIPLE = 2,
    BOTH = 3
};

// struct must be moved to RM
struct outputStruct {
    int conflictCount = 0;
    vector<Course> courseList;
}

bool compareInstructorPriority(const Instructor& left, const Instructor& right)
{
    return left.getPriority() > right.getPriority();
}

outputStruct generateSchedule(vector<Department> departments)
{
    // functionality

    //for each department
    //      sort instructors by priority
    //      assign instructors to prefered courses and times
    //      fill rest of courses with instructors/times
    //      assign rooms to courses

    for (Department department : departments)
    {
        //sort by instructor priority
        sort(department.instructorList.begin(), department.instructorList.end(), &compareInstructorPriority);
    
        //assign instructors to prefered course
        for (Instructor instructor : department.instructorList)
        {

        }

        //assign instructors to the rest of the courses
        int instructorIndex = 0;
        for (Course course : department.courseList)
        {
            if (course.getInstructor() == "UNASSIGNED")
            {
                Instructor instructor;
                do {
                    instructor = department.instructorList.at(instructorIndex);
                    instructorIndex++;
                } while (instructor.getMaxCourses() <= instructor.getCurrentlyTeaching());
                if (course.getSectionType() == "A")
                {
                    department.instructorList.at(instructorIndex).incrementCurrentlyTeaching();
                    course.setInstructor(department.instructorList.at(instructorIndex)); //this is a local copy and won't be updated. Does it need to be updated? Probably not.
                }
                else if (instructor.getNextAvailability() != -1, -1) //add function that does this to Instructor
                {
                    //set instructor unavailable at first open time (pick a 2 if possible)
                    //set instructor to course
                    //set time instructor was available to course
                    department.instructorList.at(instructorIndex).incrementCurrentlyTeaching();
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
    return validateSchedule(courses);
}

outputStruct validateSchedule(vector<Course> courses)
{
    outputStruct output;
    for (int i = 0; i < courses.size(); i++)
    {
        bool individual = false;
        // check for individual course conflicts
        // output.conflictCount++; for each conflict

        //check each field is filled
        //firewall functions will be used here

        //if class is online and has a room assigned
        if (courses.at(i).getSectionType() != 'T' && courses.at(i).getRoom() != "")  //course needs room name field
        {
            individual = true;
            output.conflictCount++;
        }

        //if class is asynchronous and has a time assigned
        if (courses.at(i).getSectionType() == 'A' && (courses.at(i).getDate() != -1 || courses.at(i).getTime() != -1))
        {
            individual = true;
            output.conflictCount++;
        }

        //if room size smaller than class max size
        if (courses.at(i).room.size < courses.at(i).getMaxEnroll())
        {
            individual = true;
            output.conflictCount++;
        }

        //update course conflict flag
        if (individual && courses.at(i).conflict%2 == 0) //should be an unnecessary check, but just to be sure
        {
            courses.at(i).conflict++;
        }

        for (int j = i+1; j < courses.size(); j++)
        {
            bool multiple = false;
            //check for conflicts between classes
            //output.conflictCount++; for each conflict

            //same CRN
            if (courses.at(i).getCRN() == courses.at(j).getCRN())
            {
                multiple = true;
                output.conflictCount++;
            }

            if (courses.at(i).getDay() == courses.at(j).getDay() && courses.at(i).getTime() == courses.at(j).getTime())//course date and time should be integer values that can be immediately returned; date and time is same
            {
                if (courses.at(i).getFirstName() == courses.at(j).getFirstName() && courses.at(i).getLastName() == courses.at(j).getLastName())//course needs instructor (name?) variable; if time and instructor is the same
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

            if (courses.at(i).conflict < 2 && multiple)
            {
                courses.at(i).conflict += 2;
            }
            if (courses.at(j).conflict < 2 && multiple)
            {
                courses.at(i).conflict += 2;
            }
        }
    }
    output.courseList = courses;
    return output;
}