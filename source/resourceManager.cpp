#include "../header/resourceManager.h"
#include <iostream>
#include<sstream>

void resourceManager(bool populated, int departmentCounter, string fileStoragePath, string generatedFilePath) {

    string generatedSchedule; //TEMPORARY STRING USED FOR TESTING, MUST BE REPLACED WITH ACTUAL GENERATED SCHEDULE (MOST LIKELY IN DIF FORMAT)
    string department[10];
    string course[10];
    string instructor[10];
    string room[10];
    vector<Course> courseList;
    vector<Instructor> instructorList;
    vector<RoomInfo> roomList;
    Department departmentObject;

    fstream file;

    if(populated) {

        file.open(fileStoragePath, fstream::in);

        if(file.is_open()) {

            for(int i = 0; i < departmentCounter; i++) {

                getline(file, department[i]);

                getline(file, course[i]);

                getline(file, instructor[i]);

                getline(file, room[i]);

            }

        }

        file.close();

        file.open(generatedFilePath, std::fstream::out | std::fstream::trunc);

            //LINK GENERATED SCHEDULE BELOW
            //DUMMY INPUT PROVIDED AS OF 3/20/2023 - Campbell :)

        generatedSchedule = "Hello!\n\nThis is a dummy schedule generation.\n\nThis functionality is currently WIP!";

        if(file.is_open())
            file << generatedSchedule;

        file.close();

    }

    // Populate courseList
	file.open(course[0], fstream::in);
	if (file.is_open()) {
		string data;
        getline(file, data);    // Skip title header

		while (getline(file, data)) {
			courseList.push_back(createCourse(data));
        }

        file.close();
    }

	// Populate instructorList
	file.open(instructor[0], fstream::in);
	if (file.is_open()) {
		string data;
		getline(file, data);    // Skip title header

		while (getline(file, data)) {
			instructorList.push_back(createInstructor(data));
		}

		file.close();
	}

	// Populate roomList
	file.open(room[0], fstream::in);
	if (file.is_open()) {
		string data;
		getline(file, data);    // Skip title header

		while (getline(file, data)) {
			roomList.push_back(createRoom(data));
		}

		file.close();
    }

	// Create Department object
    departmentObject.courseList = courseList;
    departmentObject.instructorList = instructorList;
    departmentObject.roomList = roomList;
}

Instructor createInstructor(string data) {
	vector<string> splitData;
    Instructor instructorObject;

	// Split data on commas
	stringstream analyze(data);
	while (analyze.good()) {
        string substr;
		getline(analyze, substr, ',');
		splitData.push_back(substr);
    }

	// Create instructor object
	instructorObject.setLastName(splitData[0]);
	instructorObject.setFirstName(splitData[1]);
	if (splitData[0] == "" && splitData[1] == "") { cout << "ERROR: Instructor does not exist" << endl; }

	try { instructorObject.setMaxCourses(stoi(splitData[2])); }
	catch (...) { cout << "ERROR: Max courses not set to a number" << endl; }
    
	try { instructorObject.setPriority(stoi(splitData[3])); }
    catch (...) { cout << "ERROR: Max courses not set to a number" << endl; }

    instructorObject.setPreferredClass(splitData[4]);

    // Transform vector of strings into schedule
	try {
		for (int i = 5; i < 12; ++i) {
			instructorObject.setOccupied(0, i - 5, stoi(splitData[i]));
		}
		for (int i = 12; i < 19; ++i) {
			instructorObject.setOccupied(1, i - 12, stoi(splitData[i]));
		}
	}
	catch (...) { cout << "ERROR: Schedule not set to a number" << endl; }
	
    return instructorObject;
}

Course createCourse(string data) {
	vector<string> splitData;
	Course courseObject;

	// Split data on commas
	stringstream analyze(data);
	while (analyze.good()) {
		string substr;
        getline(analyze, substr, ',');
        splitData.push_back(substr);
    }

	// Create course object
	try { courseObject.setCRN(stoi(splitData[0])); }
	catch (...) { cout << "ERROR: Course not set to a number" << endl; }
    
	courseObject.setCourseNumber(splitData[1]);
	courseObject.setSectionNumber(splitData[2]);

	try { courseObject.setSectionType(splitData[3][0]); }
	catch (...) { cout << "ERROR: Course not a single letter" << endl; }

	try { courseObject.setTitle(splitData[4]); }
	catch (...) { cout << "ERROR: Section Schedule not set to a number" << endl; }

    courseObject.setCredit(stod(splitData[5]));

	try { courseObject.setMaxEnroll(stoi(splitData[6])); }
	catch (...) { cout << "ERROR: Schedule not set to a number" << endl; }

    return courseObject;
}

RoomInfo createRoom(string data){
	vector<string> splitData;
	RoomInfo roomObject;

	// Split data on commas
	stringstream analyze(data);
	while (analyze.good()) {
		string substr;
		getline(analyze, substr, ',');
		splitData.push_back(substr);
	}

    // Create instructor object
	roomObject.setBuildingName(splitData[0]);
	roomObject.setRoomNumber(splitData[1]);
	try { roomObject.setCapacity(stoi(splitData[2])); }
	catch (...) { cout << "ERROR: Capacity not set to a number" << endl; }

	// Transform vector of strings into schedule
	try {
		for (int i = 3; i < 10; ++i) {
			roomObject.setOccupied(0, i - 3, stoi(splitData[i]));
		}
		for (int i = 10; i < 17; ++i) {
			roomObject.setOccupied(1, i - 10, stoi(splitData[i]));
		}
	}
	catch (...) { cout << "ERROR: Schedule not set to a number" << endl; }

	return roomObject;
}
