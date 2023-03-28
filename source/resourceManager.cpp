#include "../header/resourceManager.h"

void resourceManager(bool populated, int departmentCounter, string fileStoragePath, string generatedFilePath) {

    string generatedSchedule; //TEMPORARY STRING USED FOR TESTING, MUST BE REPLACED WITH ACTUAL GENERATED SCHEDULE (MOST LIKELY IN DIF FORMAT)
    string department[10];
    string course[10];
    string instructor[10];
    string room[10];

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

}



