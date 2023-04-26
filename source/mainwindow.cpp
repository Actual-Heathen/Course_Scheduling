#include "../header/mainwindow.h"
#include "./ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowState(Qt::WindowMaximized); //start gui in maximized window state

    w.show();

    return a.exec();

}


//Constructor for MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->GenerateButton->hide();

    ui->SaveCSVButton->hide();

    ui->SaveTXTButton->hide();

    ui->ConflictLine->hide();

    ui->ValidateButton->hide();

    fileStoragePath = "filePathStorage.txt"; //static file path

    generatedCSVPath = "output.csv"; //static file path

    departmentCounter = 0;

    conflictCounter = 0;

    populated = false; //used to tell resourceManager if the files were populated, bad implementation - reimplement later - 4/5/2023

    darkMode = false; //used to transition to and from dark mode

    scheduleGenerated = false; //used to determine displaying of schedule widget

    on_DepartmentButton_clicked(); //initialize gui with 1 department input

}


//Deconstructor of MainWindow
MainWindow::~MainWindow()
{

    delete ui;

}


//Grabs all the filepaths and department names from department inputs and stores them in the a local .txt file for backend use, then accesses the output.csv via additional called functions to display the schedule
void MainWindow::on_GenerateButton_clicked()
{

    bool error1 = false;

    bool error2 = false;

    int indexPosition = 0;

    int badInput[departmentCounter][4]; //bad input tracking

    QStringList rowData;

    QFile file(fileStoragePath);

    QTextStream stream(&file); //file stream for .txt file

    if(file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) { //if file is opened, file created if not existant, file overwritten if already existing

        populated = false;

        QMultiMap<QHBoxLayout*, QWidget*>::iterator index; //used to access every department input layout

        for(index = DepartmentMap.begin(); index != DepartmentMap.end(); index = DepartmentMap.upperBound(index.key())) { //iterate through DepartmentLayoutMap's DepartmentLayouts to get every possible file provided

            QList<QWidget*> values = DepartmentMap.values(index.key()); //store values of DepartmentLayout within list

            QLineEdit* DepartmentAcronym = qobject_cast<QLineEdit*>(values[6]); //store DepartmentLine

            QLineEdit* CourseLine = qobject_cast<QLineEdit*>(values[4]); //store CourseLine

            QLineEdit* InstructorLine = qobject_cast<QLineEdit*>(values[2]); //store InstructorLine

            QLineEdit* RoomLine = qobject_cast<QLineEdit*>(values[0]); //store RoomLine

            if(check_Department_Acronym(DepartmentAcronym->text())) {

                stream << DepartmentAcronym->text().toUpper() << "\n"; //grab Department Name and store it in file

                DepartmentAcronym->setStyleSheet(""); //clear any error checking

                badInput[indexPosition][0] = 0; //no error

            }else {

                DepartmentAcronym->setStyleSheet("border-color: red; border-width: 2px;"); //display error location

                badInput[indexPosition][0] = 1; //record error

            }

            if(check_File_Extension(CourseLine->text())){

                stream << CourseLine->text() << "\n"; //grab Course File Path and store it in file

                CourseLine->setStyleSheet(""); //clear any error checking

                badInput[indexPosition][1] = 0; //no error

            }else {

                CourseLine->setStyleSheet("border-color: red; border-width: 2px;"); //display error location

                badInput[indexPosition][1] = 2; //record error

            }

            if(check_File_Extension(InstructorLine->text())) {

                stream << InstructorLine->text() << "\n"; //grab Instructor File Path and store it in file

                InstructorLine->setStyleSheet(""); //clear any error checking

                badInput[indexPosition][2] = 0; //no error

            }else {

                InstructorLine->setStyleSheet("border-color: red; border-width: 2px;"); //display error location

                badInput[indexPosition][2] = 2; //record error

            }

            if(check_File_Extension(RoomLine->text())) {

                stream << RoomLine->text() << "\n"; //grab Room File Path and store it in file

                RoomLine->setStyleSheet(""); //clear any error checking

                badInput[indexPosition++][3] = 0; //no error

            }else {

                RoomLine->setStyleSheet("border-color: red; border-width: 2px;"); //display error location

                badInput[indexPosition++][3] = 2; //record error

            }

        }

    }

    file.close();

    for(int x = 0; x < indexPosition; x++){ //for loop to iterate through badInput to check for bad inputs

        for(int y = 0; y < 4; y++) {

            switch(badInput[x][y]) {

            case 1: //bad department acronym input

                error1 = true;

                break;

            case 2: //bad department csv input

                error2 = true;

                break;

            }

        }

    }

    if(error1 == false && error2 == false) { //if no errors are found

        scheduleGenerated = true;

        populated = true;

        conflictCounter = resourceManager(populated, departmentCounter, fileStoragePath.toStdString()); //call resourceManager to generate schedule, which returns number of conflicts

        rowData = get_File_Data(); //get data from file and store it in a List

        initialize_Table(rowData.size()); //initialize data, while also sending number of rows to generate

        populate_Table(rowData); //populate table with data found from the file, by passing in rowData

        find_Conflicts(); //highlights the conflicts within the schedule

        populated = false;

        display_Generated_Schedule(); //display necessary changes

    }else { //if errors are found

        clear_Table(); //delete table

        QMessageBox messageBox;

        QString error;

        if(error1 == true && error2 == true)
            error = "Invalid Department Acronym!\n\nInvalid Input Provided!";
        else if (error1 == true)
            error = "Invalid Department Acryonym!";
        else
            error = "Invalid Input Provided!";


        messageBox.critical(0,"ERROR",error); //display message to user with appropriate error content

    }

}


//Check to make sure the inputted department acronym is valid
bool MainWindow::check_Department_Acronym(QString departmentAcronym)
{

    if(departmentAcronym.size() < 4) //size checking
        if(departmentAcronym.size() > 1)
            return true; //good acronym

    return false; //bad acronym

}


//Check to make sure the inputted department file is a csv
bool MainWindow::check_File_Extension(QString filePath)
{

    if(filePath != "") { //check for file path input

        QStringList text = filePath.split("."); //parse the file path

        if(text[text.size()-1] == "csv") //if file is a csv
            return true;

    }

    return false; //no/bad file input provided

}


//Save the generated schedule as a csv while notifying the user of any existing conflicts
void MainWindow::on_SaveCSVButton_clicked()
{

    if(conflictCounter > 0) { //if there are conflicts

        QMessageBox messageBox;

        messageBox.warning(0,"WARNING","You are saving a schedule with conflicts!"); //alert user

    }

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Choose Save Location"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); //have user select save location

    filePath = filePath + "/schedule.csv"; //generate file path

    if (QFile::exists(filePath)) //delete if already existant
        QFile::remove(filePath);

    QFile::copy(generatedCSVPath, filePath); //copy generated schedule csv to desired path

}


//Save the generated schedule as a txt while notifying the user of any existing conflicts
void MainWindow::on_SaveTXTButton_clicked()
{

    if(conflictCounter > 0) { //if conflicts exist

        QMessageBox messageBox;

        messageBox.warning(0,"WARNING","You are saving a schedule with conflicts!"); //alert user

    }

    get_Table_Data(); //update output.csv with table data incase of changes

    QStringList rowData = get_File_Data(); //read in output.csv data

    QString row;

    QStringList courses;

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Choose Save Location"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "/schedule.txt"; //have user select save location

    QFile file(filePath); //grab filePath

    if (file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate)) { //open schedule.txt file

        QTextStream stream(&file);

        stream.setFieldAlignment(QTextStream::FieldAlignment::AlignLeft); //input formatting

        //input header to schedule.txt via formatting
        stream << qSetFieldWidth(9) << "Sec Type" << qSetFieldWidth(7) << "CRN" << qSetFieldWidth(11) << "Course" << qSetFieldWidth(31) << "Title" << qSetFieldWidth(7) << "Course" << qSetFieldWidth(9) << "Max Enrl" << qSetFieldWidth(8) << "Days" << qSetFieldWidth(9) << "Start" << qSetFieldWidth(9) << "End" << qSetFieldWidth(6) << "Bldg" << qSetFieldWidth(11) << "Room" << qSetFieldWidth(35) << "Instructor" << qSetFieldWidth(1) << "\n";

        //input border to schedule.txt via formatting
        stream << qSetFieldWidth(9) << "--------" << qSetFieldWidth(7) << "------" << qSetFieldWidth(11) << "----------" << qSetFieldWidth(31) << "------------------------------" << qSetFieldWidth(7) << "------" << qSetFieldWidth(9) << "--------" << qSetFieldWidth(8) << "-------" << qSetFieldWidth(9) << "--------" << qSetFieldWidth(9) << "--------" << qSetFieldWidth(6) << "-----" << qSetFieldWidth(11) << "----------" << qSetFieldWidth(35) << "-----------------------------------" << qSetFieldWidth(1) << "\n";

        for(int x = 1; x < rowData.size(); x++) { //iterate through data collected from output.csv

            int y = 1;

            row = rowData[x]; //grab row x

            courses = row.split(","); //split each row via ,

            //input corresponding schedule data to schedule.txt via formatting
            stream << qSetFieldWidth(9) << courses[y++] << qSetFieldWidth(7) << courses[y++] << qSetFieldWidth(11) << courses[y++] << qSetFieldWidth(31) << courses[y++] << qSetFieldWidth(7) << courses[y++] << qSetFieldWidth(9) << courses[y++] << qSetFieldWidth(8) << courses[y++] << qSetFieldWidth(9) << courses[y++] << qSetFieldWidth(9) << courses[y++] << qSetFieldWidth(6) << courses[y++] << qSetFieldWidth(11) << courses[y++] << qSetFieldWidth(35) << courses[y++].trimmed() << qSetFieldWidth(1) << "\n";

        }

        file.close();

    }

}


//Generate a new row of department inputs
void MainWindow::on_DepartmentButton_clicked()
{

    if(departmentCounter > 0) { //minor page manipluation when adding a department input row

        if(ui->scrollArea_2->height() < 289) { //limit the number of times the page will expand, if beyond a scroll bar will appear

            ui->scrollArea_2->setFixedHeight(ui->scrollArea_2->height()+31); //increase widget size

            ui->ScheduleFrame->move(0, ui->ScheduleFrame->y()+31); //move widget

        }

    }

    ui->GenerateButton->show(); //if department input exists

    departmentCounter++;

    QVBoxLayout* Layout = qobject_cast<QVBoxLayout*>(ui->additionalDepartmentLayout->layout()); //create layout variable to gui

    QHBoxLayout* DepartmentLayout = new QHBoxLayout(ui->DepartmentFrame); //create new layout variable for new department

    QPushButton* RemoveButton = new QPushButton(("Remove Department"), ui->DepartmentFrame); //create removebutton

    RemoveButton->setFixedHeight(24);

    RemoveButton->setFixedWidth(120);

    QPushButton* CourseButton = new QPushButton("Choose File", ui->DepartmentFrame); //create coursebutton

    CourseButton->setFixedHeight(24);

    CourseButton->setFixedWidth(80);

    QPushButton* InstructorButton = new QPushButton("Choose File", ui->DepartmentFrame); //create instructor button

    InstructorButton->setFixedHeight(24);

    InstructorButton->setFixedWidth(80);

    QPushButton* RoomButton = new QPushButton("Choose File", ui->DepartmentFrame); //create roombutton

    RoomButton->setFixedHeight(24);

    RoomButton->setFixedWidth(80);

    QLineEdit* DepartmentLine = new QLineEdit(ui->DepartmentFrame); //create departmentline

    DepartmentLine->setPlaceholderText("Department Acronym");

    DepartmentLine->setFixedHeight(24);

    QLineEdit* CourseLine = new QLineEdit(ui->DepartmentFrame); //create courseline

    CourseLine->setFixedHeight(24);

    CourseLine->setReadOnly(true);

    CourseLine->setPlaceholderText("Course File");

    QLineEdit* InstructorLine = new QLineEdit(ui->DepartmentFrame); //create instructorline

    InstructorLine->setFixedHeight(24);

    InstructorLine->setReadOnly(true);

    InstructorLine->setPlaceholderText("Instructor File");

    QLineEdit* RoomLine = new QLineEdit(ui->DepartmentFrame); //create roomline

    RoomLine->setFixedHeight(24);

    RoomLine->setReadOnly(true);

    RoomLine->setPlaceholderText("Room File");

    //add all buttons and lines to generated department layout
    DepartmentLayout->addWidget(RemoveButton);

    DepartmentLayout->addWidget(DepartmentLine);

    DepartmentLayout->addWidget(CourseButton);

    DepartmentLayout->addWidget(CourseLine);

    DepartmentLayout->addWidget(InstructorButton);

    DepartmentLayout->addWidget(InstructorLine);

    DepartmentLayout->addWidget(RoomButton);

    DepartmentLayout->addWidget(RoomLine);

    Layout->insertLayout(departmentCounter-1, DepartmentLayout); //add new department layout to ui layout

    //link buttons & lines to new department layout
    DepartmentMap.insert(DepartmentLayout, RemoveButton);

    DepartmentMap.insert(DepartmentLayout, DepartmentLine);

    DepartmentMap.insert(DepartmentLayout, CourseButton);

    DepartmentMap.insert(DepartmentLayout, CourseLine);

    DepartmentMap.insert(DepartmentLayout, InstructorButton);

    DepartmentMap.insert(DepartmentLayout, InstructorLine);

    DepartmentMap.insert(DepartmentLayout, RoomButton);

    DepartmentMap.insert(DepartmentLayout, RoomLine);

    //link buttons to necessary functions
    QObject::connect(RemoveButton, &QPushButton::clicked, this, &MainWindow::on_RemoveButton_clicked);

    QObject::connect(CourseButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

    QObject::connect(InstructorButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

    QObject::connect(RoomButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

}


//Remove department layout if corresponding remove button is clicked
void MainWindow::on_RemoveButton_clicked()
{

    if(departmentCounter < 10) //check to see if there needs to be page manipulations
        if(departmentCounter > 1) { //don't manipulate page if there are no departments left

            ui->scrollArea_2->setFixedHeight(ui->scrollArea_2->height()-31);

            ui->ScheduleFrame->move(0, ui->ScheduleFrame->y()-31);

        }

    bool deleted = false;

    departmentCounter--; //decrement counter to represent loss of a department input

    QPushButton* RemoveButton = qobject_cast<QPushButton*>(sender()); //grab RemoveButton that was clicked to find the right DepartmentLayout

    QHBoxLayout* key;

    QMultiMap<QHBoxLayout*, QWidget*>::iterator index;

    for(index = DepartmentMap.begin(); index != DepartmentMap.end(); index = DepartmentMap.upperBound(index.key())) { //check every DepartmentLayout to find the selected on

        QList<QWidget*> values = DepartmentMap.values(index.key()); //store values of DepartmentLayout in value list

        for (int i = 0; i < values.size(); ++i) { //iterate through all values within the value list to see if this is the right DepartmentLayout

            if(values.at(i) == RemoveButton) { //if right DepartmentLayout is found

                key = index.key();

                while (key->count() != 0) { //increment through every widget within the key and delete it

                    QLayoutItem* Item = key->takeAt(0);

                    delete Item->widget();

                    delete Item;

                }

                DepartmentMap.remove(key); //remove key from the map

                deleted = true;    //End search for deletion

            }

            if(deleted)
                break;

        }

        if(deleted)
            break;

    }

    if(departmentCounter == 0) //if all departments are removed, the user can't generate a schedule
        ui->GenerateButton->hide();

}


//Validate the schedule pulled from schedule widget
void MainWindow::on_ValidateButton_clicked()
{

    get_Table_Data(); //get data from table widet

    int oldConflictCounter = conflictCounter; //storage for conflict counter

    conflictCounter = outToIn(); //grab new conflict counter + call backend to validate schedule

    QStringList rowData = get_File_Data(); //grab validated schedule data

    clear_Table(); //clear table

    initialize_Table(rowData.size()); //create table

    populate_Table(rowData); //populate table

    find_Conflicts(); //make conflicted rows red

    if(oldConflictCounter != conflictCounter) //if number of conflcits has changed
        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter)); //update display

    if(conflictCounter == 0) { //if no conflcits exist, hide conflict/validate interface

        ui->ConflictLine->hide();

        ui->ValidateButton->hide();

    }

    scheduleValidated = true;

    display_Generated_Schedule();

}


//Swap interface between darkmode and lightmode stylesheets
void MainWindow::on_DarkModeAction_triggered()
{

    if(!darkMode) { //lightmode enabled, enable darkmode

        ui->centralWidget->setStyleSheet("QWidget{background: black; border-style: outset; border-color: dimgrey; color: gainsboro;}"
                                         "QPushButton{border-width: 1px; color: white; background-color: dimgrey;}"
                                         "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                         "QLineEdit{border-width:2px; color: gainsboro; background-color: black}"
                                         "QTableWidget{border-color: dimgrey; border-width: 2px; alternate-background-color: dimgrey; gridline-color: white;}"
                                         "QHeaderView::section{background-color: black; color: gainsboro;}"
                                         "QTableCornerButton::section{background-color: black; border-color: dimgray; border-width: 2px;}");

        ui->menuBar->setStyleSheet("QMenuBar{background-color: black; color: gainsboro;}"
                                   "QMenuBar::item{background-color: black;}"
                                   "QMenuBar::item:selected{background-color: rgba(115, 201, 250, 0.4);}"
                                   "QMenu{background: dimgrey; color:gainsboro;}"
                                   "QMenu::item:selected{background-color: rgba(115, 201, 250, 0.4);}");

        darkMode = true;

    } else { //enable lightmode

        ui->centralWidget->setStyleSheet("QWidget{background-color: white; border-style: outset; border-color: black; color: black;}"
                                         "QLineEdit{border-width:1px; color: black; background-color: white}"
                                         "QPushButton{border-width: 1px; color: black; background-color: white;}"
                                         "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                         "QPlainTextEdit{border-width: 1px;}"
                                         "QTableWidget{border-color: black; border-width: 1px; alternate-background-color: lightgrey; gridline-color: black;}"
                                         "QHeaderView::section{background-color: white; color: black;}"
                                         "QTableCornerButton::section{background-color: white; border-color: black; border-width: 1px;}");

        ui->menuBar->setStyleSheet("QMenuBar{background-color: white; color: black;}"
                                   "QMenuBar::item:selected{background-color: rgba(115, 201, 250, 0.4);}"
                                   "QMenu{background: white; color:black;}"
                                   "QMenu::item:selected{background-color: rgba(115, 201, 250, 0.4);}");

        darkMode = false;

    }

}


//Displays necessary schedule/ui info to user
void MainWindow::display_Generated_Schedule()
{

    ui->SaveCSVButton->show();

    ui->SaveTXTButton->show();

    if(conflictCounter > 0) {

        ui->ValidateButton->show();

        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter)); //display number of conflicts found

        ui->ConflictLine->show();

    }

}


//Allows user to select file for selected department file input
void MainWindow::find_File_Path()
{

    bool found = false;

    QPushButton* fileButton = qobject_cast<QPushButton*>(sender()); //grab FileButton that was clicked to find the right DepartmentLayout

    QMultiMap<QHBoxLayout*, QWidget*>::iterator index;

    for(index = DepartmentMap.begin(); index != DepartmentMap.end(); index++) { //check every DepartmentLayout to find the selected on

        QList<QWidget*> value = DepartmentMap.values(index.key()); //store values of DepartmentLayout in value list

        for (int i = 0; i < value.size(); ++i) { //iterate through all values within the value list to see if this is the right DepartmentLayout

            if(value.at(i) == fileButton) { //if right DepartmentLayout is found

                QWidget* widget = value.at(i-1); //get the lineEdit corresponding to the selected file button

                QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget);

                QString filePath = QFileDialog::getOpenFileName(this, "Choose File"); //prompt user to find file in File Explorer

                QFile file(filePath); //grab filePath

                if (!file.open(QFile::ReadWrite | QFile::Text)) { //if no file selected/file nonexistant

                    lineEdit->setText("File Not Found!");

                }else { //file found, populate lineEdit

                    lineEdit->setText(filePath);

                }

                file.close();

                found = true; //fileButton was found

            }

            if(found)
                break;

        }

        if(found)
            break;

    }

}


//Grabs and returns schedule data from output.csv
QStringList MainWindow::get_File_Data()
{

    QStringList rowData;

    QString data;

    QFile file(generatedCSVPath);

    QTextStream stream(&file);

    if(file.open(QFile::ReadOnly)) { //open file to read if it exists

        data = stream.readAll(); //read all data

        rowData = data.split("\n"); //split rows up

    }

    file.close();

    return rowData; //return data

}


//Create the Table Widget
void MainWindow::initialize_Table(int numRows)
{

    if(scheduleGenerated) //if schedule was previously generated
        clear_Table();

    auto table = ui->scheduleTable;

    ComboBoxDelegate* comboSecType = new ComboBoxDelegate(table);

    ComboBoxDelegate2* comboDay = new ComboBoxDelegate2(table);

    ComboBoxDelegate3* comboStart = new ComboBoxDelegate3(table);

    ComboBoxDelegate4* comboEnd = new ComboBoxDelegate4(table);

    table->setRowCount(numRows-1); //number of rows -1 to prevent inclusion of header row of csv

    table->setColumnCount(numColumns); //Generate number of columns

    table->setItemDelegateForColumn(1, comboSecType); //Set interaction restrictions for said column

    table->setItemDelegateForColumn(7, comboDay); //Set interaction restrictions for said column

    table->setItemDelegateForColumn(8, comboStart); //Set interaction restrictions for said column

    table->setItemDelegateForColumn(9, comboEnd); //Set interaction restrictions for said column

    QString headerCell[numColumns] = {"Conflict", "Section Type", "CRN", "Course", "Title", "Credit", "Max Enrollment", "Days", "Start", "End", "Building", "Room", "Instructor"}; //store set column header text

    for(int y = 0; y < numColumns; y++) { //iterate through columns and set their header

        auto item = new QTableWidgetItem; //item to store header text

        item->setText(headerCell[y]); //set text of item

        table->setHorizontalHeaderItem(y, item); //set header

        for (int x = 0; x < numRows; x++) { //iterate through every row and add interactable cells

            auto cell = new QTableWidgetItem;

            table->setItem(x, y, cell);

            if (y == 0)
                cell->setFlags(cell->flags() & ~Qt::ItemIsEnabled); //disable conflict column so user can't change conflict identifier

        }

    }

    table->setSortingEnabled(true); //enable table to sort alphabetically/numerically via header cells

}


//Populate the Table Widget with generated schedule
void MainWindow::populate_Table(QStringList rowData)
{

    auto table = ui->scheduleTable;

    QString cellData;

    QStringList cell;

    for (int x = 0; x < rowData.size(); x++) { //grab every row data from list parameter

        cellData = rowData[x]; //grab a single row

        if(x >= 1) { //once past header

            cell = cellData.split(","); //split row data

            for (int y = 0; y < cell.size(); y++) { //iterate through every cell of the row and set the cell's text as the data from generated schedule

                table->item(x-1, y)->setText(cell[y]);

            }

        }

    }

}


//Grab data from table widget and store it in output.csv
void MainWindow::get_Table_Data()
{

    QFile file(generatedCSVPath);

    QTextStream stream(&file);

    if(file.open(QFile::WriteOnly)) { //once file is open/exists

        auto table = ui->scheduleTable;

        stream << "Conflict,Section Type,CRN,Course,Title,Credit,Max Enrollment,Days,Start,End,Building,Room,Instructor\n"; //set header row

        for (int x = 0; x < table->rowCount(); x++) { //iterate through every row

            for (int y = 0; y < table->columnCount(); y++) { //iterate through ever column of said row

                stream << table->item(x,y)->text(); //read in text from cell

                if(y+1 < table->columnCount()) //check for end of table
                    stream << ","; //if not end, add ,

            }

            if(x+1<table->rowCount()) //end of table (last column read in)
                stream << "\n"; //add newline indicator

        }

    }

    file.close();

}


//Iterates through every row in column 0 (conflict column) and checks to see if the row needs to be red to signify conflict
void MainWindow::find_Conflicts()
{

    auto table = ui->scheduleTable;

    for (int x = 0; x < table->rowCount(); x++) { //iterate through every row

        if(table->item(x, 0)->text() != "None") { //If conflict exists

            for (int y = 0; y < table->columnCount(); y++) { //iterate through every cell and highlight it red to signify conflict

                table->item(x, y)->setBackground(QBrush(QColor("lightcoral")));

            }

        }

    }

}


//Clears the table and hides gui buttons and interactions
void MainWindow::clear_Table()
{

    auto table = ui->scheduleTable;

    table->setRowCount(0);

    table->setColumnCount(0);

    scheduleGenerated = false;

    ui->ConflictLine->hide();

    ui->ValidateButton->hide();

    ui->SaveCSVButton->hide();

    ui->SaveTXTButton->hide();

}


//Menu button to add department
void MainWindow::on_actionAdd_Department_triggered()
{

    on_DepartmentButton_clicked();

}


//Menu button to generate schedule
void MainWindow::on_actionGenerate_Schedule_triggered()
{
    if(departmentCounter > 0) //if department input exists
        on_GenerateButton_clicked();

}


//Menu button to validate schedule
void MainWindow::on_actionValidate_Schedule_triggered()
{

    if(!ui->ValidateButton->isHidden()) //if schedule is generated
        on_ValidateButton_clicked();
    else { //no schedule generated

        QMessageBox messageBox;

        messageBox.critical(0, "ERROR", "No Schedule Generated!"); //alert user

    }

}


//Menu button to save schedule as csv
void MainWindow::on_actionSave_as_CSV_triggered()
{

    if(scheduleGenerated) //if schedule is generated
        on_SaveCSVButton_clicked();
    else { //no schedule generated

        QMessageBox messageBox;

        messageBox.critical(0, "ERROR", "No Schedule Generated!"); //alert user

    }

}


//Menu button to save schedule as txt
void MainWindow::on_actionSave_to_Print_triggered()
{

    if(scheduleGenerated) //if schedule exists
        on_SaveTXTButton_clicked();
    else { //no schedule generated

        QMessageBox messageBox;

        messageBox.critical(0, "ERROR", "No Schedule Generated!"); //alert user

    }

}


//Menu button to display legend describing schedule info
void MainWindow::on_actionLegend_triggered()
{

    QMessageBox messageBox;

    //Display legend to user
    messageBox.information(0, "Legend", "TBA - If a schedule cell contains 'TBA' after schedule generation, that could mean one of two things:\n\n\t1) The current course is listed as an Online course\n\n\t2) Information could not be assigned to the course due within\n\t    generation of the schedule"
                                        "\n\nRed Row - If a schedule row is highlighted in red, that is signifying that said course has 1 or more conflicts that should be resolved"
                                        "\n\nTypes of Conflicts - There are two possible types of conflicts that can occur during schedule generation:\n\n\t1) Self Conflicts - These conflicts are the result of when a course is\n\t\t               generated and certain parts of the information\n\t\t               provided is impossible\n\n\t2) Shared Conflicts - These conflicts are the result of when two or more\n\t\t                     courses share the same information after\n\t\t                     generation");

}

