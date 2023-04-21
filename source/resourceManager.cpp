#include "../header/resourceManager.h"
#include <iostream>
#include<sstream>
#include<string>
#include <map>

int resourceManager(bool populated, int departmentCounter, string fileStoragePath) {
    int errorNumber = -1;    // TEMPORARY VALUE USED TO REPRESENT FILE ERROR
    int allGood = 0;   // TEMPORARY VALUE USED TO REPRESENT GOOD EXECUTION

    vector<string> department(departmentCounter,"");
    vector<string> course(departmentCounter,"");
    vector<string> instructor(departmentCounter,"");
    vector<string> room(departmentCounter,"");

    map<string, RoomInfo> roomMap;
    vector<Department> departmentList;
    fstream file;

    if(populated) { //previously there was a "generatedFilePath.txt" file generated, however what ever dumbass implemented that (me) didn't think it through as it is not necessary. For accessing the generated schedule, a hardcoded path to schedule.csv will be used.

        file.open(fileStoragePath, fstream::in);

        if(file.is_open()) {

            for(int i = 0; i < departmentCounter; i++) {

                getline(file, department.at(i));

                getline(file, course.at(i));

                getline(file, instructor.at(i));

                getline(file, room.at(i));

            }

        }

        file.close();
    }

    // Create a Department object and map rooms for each entry
    for (int entry = 0; entry < departmentCounter; ++entry) {
        cout << "\nGenerating new schedule" << endl;
		
    	Department departmentObject;
		departmentObject.setName(department.at(entry));

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
			
			getline(file, data);    // Skip title header

			try {
				while (getline(file, data)) {
					RoomInfo roomObject = createRoom(data);
					string roomName = "";
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
    outputStruct output = generateSchedule(departmentList, roomMap);
	int conflicts = toOutput(output);
	return conflicts;
}

/*
write generated schedule to file, return number of conflicts detected
*/
int toOutput(outputStruct results) //conf,type,crn,couresenum,name,max,days,start,end,bld,room,instructor
{
	ofstream csvOutput;
    csvOutput.open("output.csv");

	csvOutput << "Conflict,Sec Type,CRN,Course,Title,Credit,Max Enrl,Days,Start,End,Bldg,Room,Instructor\n";

	for (long unsigned int i = 0; i < results.courseList.size(); i++)
	{
		csvOutput << results.courseList[i].conflictToString() << ",";
		csvOutput << results.courseList[i].getSectionType() << ",";
		csvOutput << results.courseList[i].getCRN() << ",";
		csvOutput << results.courseList[i].getCourseNumber() << " " << results.courseList[i].getSectionNumber() << ",";
		csvOutput << results.courseList[i].getTitle() << ",";
		csvOutput << results.courseList[i].getCredit() << ",";
		csvOutput << results.courseList[i].getMaxEnroll() << ",";
		int dayTime = results.courseList[i].getDay();
		if (dayTime == 0)
		{
			csvOutput <<"MW,";
		}
		else if (dayTime == 1)
		{
			csvOutput << "TR,";
		}
		else
		{
			csvOutput <<"TBA,";
		}
		dayTime = results.courseList[i].getTime();
		if (dayTime == 0)
		{
			csvOutput <<"8:00 AM,";
			csvOutput <<"9:20 AM,";
		}
		else if (dayTime == 1)
		{
			csvOutput <<"9:40 AM,";
			csvOutput <<"11:00 AM,";
		}
		else if (dayTime == 2)
		{
			csvOutput <<"11:20 AM,";
			csvOutput <<"12:40 AM,";
		}
		else if (dayTime == 3)
		{
			csvOutput <<"1:00 PM,";
			csvOutput <<"2:20 PM,";
		}
		else if (dayTime == 4)
		{
			csvOutput <<"2:40 PM,";
			csvOutput <<"4:00 PM,";
		}
		else if (dayTime == 5)
		{
			csvOutput <<"4:20 PM,";
			csvOutput <<"5:40 PM,";
		}
		else if (dayTime == 6)
		{
			csvOutput <<"6:00 PM,";
			csvOutput <<"7:20 PM,";
		}
		else
		{
			csvOutput <<"TBA,";
			csvOutput <<"TBA,";
		}
		//csvOutput << courseList[i].getBuilding() << ",";
		string buildingRoom = results.courseList[i].getRoom();
		int space = buildingRoom.find(" ");
		string building = buildingRoom.substr(0, space);
		string room = buildingRoom.substr(space+1); 

		csvOutput << building << ",";
		csvOutput << room << ",";
        csvOutput << results.courseList[i].getLastName() <<" "<< results.courseList[i].getFirstName();

        if(i+1 < results.courseList.size())
            csvOutput << "\n";

	}
	csvOutput.close();
	return results.conflictCount;
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
	getline(csvInput,line); //dump header
    while(getline(csvInput, line, '\n'))
	{
        stringstream lineS(line);
		int counter = 0;
        if(lineS.str() != ",,,,,,,,,,,,")
		{
            while(getline(lineS,temp,','))
			{

				if (counter == 3)
				{
					stringstream tempS(temp);
					vector<string> abToken;
					const char delim = ' ';
					while(getline(tempS,temp,delim))
					{
						abToken.push_back(temp);
					}

					words.push_back(abToken[0]+" "+abToken[1]); //add department and course number
					
					temp = "";

					for (int i = 2; i < abToken.size(); i++)
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
				if (counter == 12 )
				{
					stringstream tempS(temp);
					vector<string> abToken;
					const char delim = ' ';
					while(getline(tempS,temp,delim))
					{
						abToken.push_back(temp);
					}

					words.push_back(abToken[0]); //add instructor last name
					
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
			tempCourse.setConflict(NONE); //changed from true 1) to match conflict enum type, 2) to start with no conflicts; conflicts determined later in validation
			tempCourse.setSectionType(words[1].at(0));
			tempCourse.setCRN(stoi(words[2]));
			tempCourse.setCourseNumber(words[3]);
			tempCourse.setSectionNumber(words[4]);
			tempCourse.setTitle(words[5]);
			tempCourse.setCredit(stoi(words[6]));
			tempCourse.setMaxEnroll(stoi(words[7]));
			string dayTime = words[8];
			if (dayTime == "MW")
			{
				tempCourse.setDay(0);
			}
			else if (dayTime == "TR")
			{
				tempCourse.setDay(1);
			}
			else
			{
				tempCourse.setDay(-1);
			}
			dayTime = words[9];
			if (dayTime == "8:00 AM")
			{
				tempCourse.setTime(0);
			}
			else if (dayTime == "9:40 AM")
			{
				tempCourse.setTime(1);
			}
			else if (dayTime == "11:20 AM")
			{
				tempCourse.setTime(2);
			}
			else if (dayTime == "1:00 PM")
			{
				tempCourse.setTime(3);
			}
			else if (dayTime == "2:40 PM")
			{
				tempCourse.setTime(4);
			}
			else if (dayTime == "4:20 PM")
			{
				tempCourse.setTime(5);
			}
			else if (dayTime == "6:00 PM")
			{
				tempCourse.setTime(6);

			}
			else
			{
				tempCourse.setTime(-1);
			}
			//no end time (words[10])	
			//tempCourse.setBuilding(words[11]);
			if (words[11] == "TBA")
			{
				tempCourse.setRoom("TBA");
			}
			else
			{
				tempCourse.setRoom(words[11]+" "+words[12]);
			}
			tempCourse.setLastName(words[13]);
			tempCourse.setFirstName(words[14]);
			words.clear();
			
			courseList.push_back(tempCourse);
        }
	}
	outputStruct output = validateSchedule(courseList, false); //no room map generated, can't account for max capacity
	return toOutput(output);
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

    instructorObject.setPreferredCRN(stoi(splitData[4]));

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
