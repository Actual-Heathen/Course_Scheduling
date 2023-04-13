#include "../header/resourceManager.h"
#include <iostream>
#include<sstream>
#include<string>
#include <map>

int resourceManager(bool populated, int departmentCounter, string fileStoragePath) {
    int errorNumber = -1;    // TEMPORARY VALUE USED TO REPRESENT FILE ERROR
    int allGood = 0;   // TEMPORARY VALUE USED TO REPRESENT GOOD EXECUTION

    string department[departmentCounter];
    string course[departmentCounter];
    string instructor[departmentCounter];
    string room[departmentCounter];
    map<string, RoomInfo> roomMap;
    vector<Department> departmentList;
    Department departmentObject;
    fstream file;

    if(populated) { //previously there was a "generatedFilePath.txt" file generated, however what ever dumbass implemented that (me) didn't think it through as it is not necessary. For accessing the generated schedule, a hardcoded path to schedule.csv will be used.

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
    }

    // Create a Department object and map rooms for each entry
	for (int entry = 0; entry < departmentCounter; ++entry) {
        cout << "\nGenerating new schedule" << endl;

        // Populate courseList
        // If a file cannot be read, the program aborts and prints and error.
        file.open(course[entry], fstream::in);
		if (file.is_open()) {
			string data;
			getline(file, data);    // Skip title header

			try {
				while (getline(file, data)) {
					departmentObject.courseList.push_back(createCourse(data));
				}
			}
            catch (...) {
                cout << "FILE ERROR: Course file is incorrect" << endl;
                cout << "SYSTEM: Program aborted" << endl;
				return errorNumber;
			}

			file.close();
		}

		// Populate instructorList
        // If a file cannot be read, the program aborts and prints and error.
		file.open(instructor[entry], fstream::in);
		if (file.is_open()) {
			string data;
			getline(file, data);    // Skip title header

			try {
				while (getline(file, data)) {
					departmentObject.instructorList.push_back(createInstructor(data));
				}
			}
			catch (...) {
                cout << "FILE ERROR: Intructor file is incorrect" << endl;
                cout << "SYSTEM: Program aborted" << endl;
				return errorNumber;
			}

			file.close();
		}
		
		// Populate roomList and roomMap
        // If a file cannot be read, the program aborts and prints and error.
		file.open(room[entry], fstream::in);
		if (file.is_open()) {
			string data;
			string roomName;
			getline(file, data);    // Skip title header

			try {
				while (getline(file, data)) {
					RoomInfo roomObject = createRoom(data);
					roomName.append(roomObject.getBuildingName());
					roomName.append(" ");
					roomName.append(roomObject.getRoomNumber());
					departmentObject.roomList.push_back(roomName);

					roomMap.insert(pair<string, RoomInfo>(roomName, roomObject));
				}
			}
			catch (...) {
                cout << "FILE ERROR: Room file is incorrect" << endl;
                cout << "SYSTEM: Program aborted" << endl;
				return errorNumber;
			}
			
			file.close();
		}
		
		departmentList.push_back(departmentObject);
	}
	outToIn();
    return allGood;
}

int toOutput(vector<Course> courseList) //conf,type,crn,couresenum,name,max,days,start,end,bld,room,instructor
{
	ofstream csvOutput;
	csvOutput.open("output1.csv");

	//csvOutput << "Conflict,Sec Type,CRN,Course,Title,Credit,Max Enrl,Days,Start,End,Bldg,Room,Instructor\n";

	for (long unsigned int i = 0; i < courseList.size(); i++)
	{
		csvOutput << courseList[i].getConflict() << ",";
		csvOutput << courseList[i].getSectionType() << ",";
		csvOutput << courseList[i].getCRN() << ",";
		csvOutput << courseList[i].getCourseNumber() << " " << courseList[i].getSectionNumber() << ",";
		csvOutput << courseList[i].getTitle() << ",";
		csvOutput << courseList[i].getCredit() << ",";
		csvOutput << courseList[i].getMaxEnroll() << ",";
		csvOutput << courseList[i].getDay() << ",";
		csvOutput << courseList[i].getTime() << ",";
		csvOutput << courseList[i].getTime() << ",";
		csvOutput << courseList[i].getRoom() << ",";
		csvOutput << courseList[i].getRoom() << ",";
		csvOutput << courseList[i].getLastName() <<" "<< courseList[i].getFirstName() << "\n";
	}
	csvOutput.close();
	return 0;
}

int outToIn()
{
	vector<Course> courseList;
	ifstream csvInput;
	csvInput.open("output.csv");
	
	if (!csvInput)
	{
		return -1;
	}
	
	string line;
	string temp;
	vector<string> words;

	while(getline(csvInput, line))
	{
		cout<<line<<endl;
		stringstream lineS(line);
		int counter = 0;

		while(getline(lineS,temp,','))
		{

			if (counter == 3 || counter == 11)
			{
				stringstream tempS(temp);
				vector<string> abToken;
				while(getline(tempS,temp,' '))
				{
					abToken.push_back(temp);
				}

				words.push_back(abToken[0]);
				
				temp = "";

				for (int i = 1; i < abToken.size(); i++)
				{
					if (i != abToken.size()-1)
					{
						temp += abToken[i] + " ";
					}
					else
					{
						temp += abToken[i];
					}
				}
				abToken.clear();
			}
			words.push_back(temp);
			counter++;
		}

		Course tempCourse;
		tempCourse.setConflict(true);
		tempCourse.setSectionType(words[1].at(0));
		tempCourse.setCRN(stoi(words[2]));
		tempCourse.setCourseNumber(words[3]);
		tempCourse.setSectionNumber(words[4]);
		tempCourse.setTitle(words[5]);
		tempCourse.setCredit(stoi(words[6]));
		tempCourse.setMaxEnroll(stoi(words[7]));
		tempCourse.setDay(stoi(words[8]));
		tempCourse.setTime(stoi(words[9]));
		//no end time (words[10])				
		tempCourse.setRoom(words[11]);
		tempCourse.setLastName(words[12]);
		tempCourse.setFirstName(words[13]);
		
		words.clear();
		
		courseList.push_back(tempCourse);
	}
	toOutput(courseList);
	return 0;
}



int validateSchedule() {

	int conflictCounter = 0; //used to count the number of conflicts recorded during generation/validation of the schedule

	return conflictCounter; //for now this will be true, however when the validation function from engine.cpp is called, that will return a bool on if anything actually changed (i.e. conflict counter increased/decreased)?? Open to discussion on this***
}

// This function creates and returns an instructor object.
// If an entry cannot be read, the program skips it and prints and error.
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
    catch (...) { cout << "ERROR: Priority not set to a number" << endl; }

    instructorObject.setPreferredClass(splitData[4]);

    // Transform vector of strings into schedule
	try {
		for (int i = 5; i < 12; ++i) {
			instructorObject.setAvailability(0, i - 5, stoi(splitData[i]));
		}
		for (int i = 12; i < 19; ++i) {
			instructorObject.setAvailability(1, i - 12, stoi(splitData[i]));
		}
	}
	catch (...) { cout << "ERROR: Schedule not set to a number" << endl; }
	
    return instructorObject;
}

// This function creates and returns a course object.
// If an entry cannot be read, the program skips it and prints and error.
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

// This function creates and returns a room object.
// If an entry cannot be read, the program skips it and prints and error.
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
			roomObject.setAvailability(0, i - 3, stoi(splitData[i]));
		}
		for (int i = 10; i < 17; ++i) {
			roomObject.setAvailability(1, i - 10, stoi(splitData[i]));
		}
	}
	catch (...) { cout << "ERROR: Schedule not set to a number" << endl; }

	return roomObject;
}
