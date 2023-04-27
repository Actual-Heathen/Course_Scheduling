# Course Scheduling System
The Course Scheduling System is an administrative tool designed for the automated generation of a School's Department schedules.
The system works by the use of course, instructor, and room inputs detailing information on the respective files to generate a schedule on the information it has been given.
# Usage
## Inputs
The input information is accepted into the system via a CSV file containing the appropriate information per file as detailed below with a header matching the field name.
### Course
* CRN - This is a course-unique number identifier
* Course - this is the course number i.e. the 101 of 101-01
* Section - this is the section number that goes along with a course number i.e. the 01 of 101-01 
* Section Type - this is the type, of course, this is in the format of **A** **S** **T** for Asynchronous, Synchronous, and Traditional courses
* Title - This is the name of the course to be listed in the catalog
* Credit - this is the credit value of the course
* Max Enrollment - this is the maximum number of students to be allowed in this course
### Instructor
* LastName - this is the instructor's last name
* FirstName - this is the instructor's first name
* Max Number of Courses - this is the max number of courses the professor is able to teach
* Scheduling Priority - the priority of the professor in the scheduling system on a 1-3 scale, 1-lowest priority, 3-highest priority
* Desired CRN - The preferred CRN of the professor
* MW 8:00-9:20 - the professor's availability at this time slot, 0-cannot teach, 1-can teach, not preferred, 2-preferred time.
* MW 9:40-11:00
* MW 11:20-12:40
* MW 1:00-2:20
* MW 2:40-4:00
* MW 4:20-5:40
* MW 6:00-7:20
* TR 8:00-9:20 
* TR 9:40-11:00
* TR 11:20-12:40
* TR 1:00-2:20
* TR 2:40-4:00
* TR 4:20-5:40
* TR 6:00-7:20
### Rooms
* Building Abbreviation - the building's name abbreviation
* Room number - the room's number
* Max capacity - the maximum capacity of the room
* MW 8:00-9:20 - the availability of the room at this time is 0-unavailable, 1-available
* MW 9:40-11:00
* MW 11:20-12:40
* MW 1:00-2:20
* MW 2:40-4:00
* MW 4:20-5:40
* MW 6:00-7:20
* TR 8:00-9:20
* TR 9:40-11:00
* TR 11:20-12:40
* TR 1:00-2:20
* TR 2:40-4:00
* TR 4:20-5:40
* TR 6:00-7:20
## Sofware Usage
To use the Course Scheduling system, upon booting the software the desired number of departments may be added using the **ADD DEPARTMENT** button.
Afterward, the department name is to be filled out with the appropriate files per department to be loaded.
When all the files are loaded the schedule can be generated via the **GENERATE** button.
Upon generating the generated schedule will be displayed
If there are any conflicts the system will highlight the row in red to indicate the issue.
There are two possible conflicts:
* Self - the course is lacking information or has incompatible information in it.
* another course - the course has a conflicting schedule with another course.
* Both conflicts are possible at the same time
 
The user can make changes directly via the displayed spreadsheet to fix any of the flagged conflicts. When changes are made they can be verified via the **VALIDATE** button which will check if there are any conflicts and highlight them.
When a schedule is complete it can be output in a CSV format of a print-ready formatted TXT. 
# building
### Dependencies
* [Qt version 6.4.2](https://www.qt.io/)
* [MinGW version 11.2.0](https://www.mingw-w64.org/)
### Compiling
The project can be compiled and run via the QT Creator IDE.
Additionally, the project can be compiled via the command line with the use of Make and Qmake
In the root folder, the project can be compiled and run as follows
```
$ qmake
$ make
$ ./Course_Scheduling
```
