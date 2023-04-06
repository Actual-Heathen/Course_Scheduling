#include "../header/resourceManager.h"

void resourceManager(bool populated, int departmentCounter, string fileStoragePath) {

    string department[departmentCounter];
    string course[departmentCounter];
    string instructor[departmentCounter];
    string room[departmentCounter];

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

}


int validateSchedule() {

    int conflictCounter = 0; //used to count the number of conflicts recorded during generation/validation of the schedule

    return conflictCounter; //for now this will be true, however when the validation function from engine.cpp is called, that will return a bool on if anything actually changed (i.e. conflict counter increased/decreased)?? Open to discussion on this***

}



