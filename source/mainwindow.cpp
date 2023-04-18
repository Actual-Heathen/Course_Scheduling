#include "../header/mainwindow.h"
#include "./ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->GenerateButton->hide();

    ui->SaveCSVButton->hide();

    ui->SavePDFButton->hide();

    ui->ConflictLine->hide();

    ui->ValidateButton->hide();

    fileStoragePath = "../Course_Scheduling/filePathStorage.txt";

    generatedCSVPath = "../Course_Scheduling/output.csv";

    departmentCounter = 0;

    conflictCounter = 0;

    populated = false; //used to tell resourceManager if the files were populated, bad implementation - reimplement later - 4/5/2023

    darkMode = false;

    scheduleGenerated = false;

    scheduleValidated = false;

    on_DepartmentButton_clicked();

}


MainWindow::~MainWindow()
{

    delete ui;

}


void MainWindow::on_GenerateButton_clicked()
{

    bool generate = true;

    int indexPosition = 0;

    int badInput[departmentCounter][4];

    QStringList rowData;

    QFile file(fileStoragePath);

    QTextStream stream(&file);

    if(file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {

        populated = false;

        QMultiMap<QHBoxLayout*, QWidget*>::iterator index;

        for(index = DepartmentMap.begin(); index != DepartmentMap.end(); index = DepartmentMap.upperBound(index.key())) { //iterate through DepartmentLayoutMap's DepartmentLayouts to get every possible file provided

            QList<QWidget*> values = DepartmentMap.values(index.key()); //store values of DepartmentLayout within list

            QLineEdit* DepartmentName = qobject_cast<QLineEdit*>(values[6]); //store DepartmentLine

            QLineEdit* CourseLine = qobject_cast<QLineEdit*>(values[4]); //store CourseLine

            QLineEdit* InstructorLine = qobject_cast<QLineEdit*>(values[2]); //store InstructorLine

            QLineEdit* RoomLine = qobject_cast<QLineEdit*>(values[0]); //store RoomLine

            if(!DepartmentName->text().isEmpty()) {

                stream << DepartmentName->text() << "\n"; //grab Department Name and store it in file

                DepartmentName->setStyleSheet("");

                badInput[indexPosition][0] = 1;

            }else {

                DepartmentName->setStyleSheet("border-color: red; border-width: 2px;");

                badInput[indexPosition][0] = 0;

            }

            if(check_File_Extension(CourseLine->text())){

                stream << CourseLine->text() << "\n"; //grab Course File Path and store it in file

                CourseLine->setStyleSheet("");

                badInput[indexPosition][1] = 1;

            }else {

                CourseLine->setStyleSheet("border-color: red; border-width: 2px;");

                badInput[indexPosition][1] = 0;

            }

            if(check_File_Extension(InstructorLine->text())) {

                stream << InstructorLine->text() << "\n"; //grab Instructor File Path and store it in file

                InstructorLine->setStyleSheet("");

                badInput[indexPosition][2] = 1;

            }else {

                InstructorLine->setStyleSheet("border-color: red; border-width: 2px;");

                badInput[indexPosition][2] = 0;

            }

            if(check_File_Extension(RoomLine->text())) {

                stream << RoomLine->text() << "\n"; //grab Room File Path and store it in file

                RoomLine->setStyleSheet("");

                badInput[indexPosition++][3] = 1;

            }else {

                RoomLine->setStyleSheet("border-color: red; border-width: 2px;");

                badInput[indexPosition++][3] = 0;

            }

        }

    }

    file.close();

    for(int x = 0; x < indexPosition; x++){

        for(int y = 0; y < 4; y++) {

            if(badInput[x][y] == 0) {

                generate = false;

                break;

            }else
                generate = true;

        }

        if(generate == false)
            break;

    }

    if(generate) {

        scheduleGenerated = true;

        populated = true;

        conflictCounter = resourceManager(populated, departmentCounter, fileStoragePath.toStdString()); //call resourceManager to generate schedule, which returns number of conflicts

        rowData = get_File_Data(); //get data from file and store it in a List

        initialize_Table(rowData.size()); //initialize data, while also sending number of rows to generate

        populate_Table(rowData); //populate table with data found from the file, by passing in rowData

        find_Conflicts(); //highlights the conflicts within the schedule

        populated = false;

        display_Generated_Schedule();

    }else
        clear_Table();

}

bool MainWindow::check_File_Extension(QString filePath)
{

    if(filePath != "") {

        QStringList text = filePath.split(".");

        if(text[text.size()-1] == "csv")
            return true;

    }

    return false;

}


void MainWindow::on_SaveCSVButton_clicked()
{

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    filePath = filePath + "/schedule.csv";

    if (QFile::exists(filePath))
        QFile::remove(filePath);

    QFile::copy(generatedCSVPath, filePath);

}


void MainWindow::on_SavePDFButton_clicked() //Needs implementation
{



}


void MainWindow::on_DepartmentButton_clicked()
{

    if(departmentCounter > 0) {

        //ui->DepartmentFrame->setFixedHeight(ui->DepartmentFrame->height()+31);

        if(ui->scrollArea_2->height() < 289) {

            ui->scrollArea_2->setFixedHeight(ui->scrollArea_2->height()+31);

            ui->ScheduleFrame->move(0, ui->ScheduleFrame->y()+31);

        }

    }

    ui->GenerateButton->show();

    departmentCounter++;

    QVBoxLayout* Layout = qobject_cast<QVBoxLayout*>(ui->additionalDepartmentLayout->layout());

    QHBoxLayout* DepartmentLayout = new QHBoxLayout(ui->DepartmentFrame);

    QPushButton* RemoveButton = new QPushButton(("Remove Department"), ui->DepartmentFrame);

    RemoveButton->setFixedHeight(24);

    RemoveButton->setFixedWidth(120);

    QPushButton* CourseButton = new QPushButton("Choose File", ui->DepartmentFrame);

    CourseButton->setFixedHeight(24);

    CourseButton->setFixedWidth(80);

    QPushButton* InstructorButton = new QPushButton("Choose File", ui->DepartmentFrame);

    InstructorButton->setFixedHeight(24);

    InstructorButton->setFixedWidth(80);

    QPushButton* RoomButton = new QPushButton("Choose File", ui->DepartmentFrame);

    RoomButton->setFixedHeight(24);

    RoomButton->setFixedWidth(80);

    QLineEdit* DepartmentLine = new QLineEdit(ui->DepartmentFrame);

    DepartmentLine->setPlaceholderText("Department Name");

    DepartmentLine->setFixedHeight(24);

    QLineEdit* CourseLine = new QLineEdit(ui->DepartmentFrame);

    CourseLine->setFixedHeight(24);

    CourseLine->setReadOnly(true);

    CourseLine->setPlaceholderText("Course File");

    QLineEdit* InstructorLine = new QLineEdit(ui->DepartmentFrame);

    InstructorLine->setFixedHeight(24);

    InstructorLine->setReadOnly(true);

    InstructorLine->setPlaceholderText("Instructor File");

    QLineEdit* RoomLine = new QLineEdit(ui->DepartmentFrame);

    RoomLine->setFixedHeight(24);

    RoomLine->setReadOnly(true);

    RoomLine->setPlaceholderText("Room File");

    DepartmentLayout->addWidget(RemoveButton);

    DepartmentLayout->addWidget(DepartmentLine);

    DepartmentLayout->addWidget(CourseButton);

    DepartmentLayout->addWidget(CourseLine);

    DepartmentLayout->addWidget(InstructorButton);

    DepartmentLayout->addWidget(InstructorLine);

    DepartmentLayout->addWidget(RoomButton);

    DepartmentLayout->addWidget(RoomLine);

    Layout->insertLayout(departmentCounter-1, DepartmentLayout);

    DepartmentMap.insert(DepartmentLayout, RemoveButton);

    DepartmentMap.insert(DepartmentLayout, DepartmentLine);

    DepartmentMap.insert(DepartmentLayout, CourseButton);

    DepartmentMap.insert(DepartmentLayout, CourseLine);

    DepartmentMap.insert(DepartmentLayout, InstructorButton);

    DepartmentMap.insert(DepartmentLayout, InstructorLine);

    DepartmentMap.insert(DepartmentLayout, RoomButton);

    DepartmentMap.insert(DepartmentLayout, RoomLine);

    QObject::connect(RemoveButton, &QPushButton::clicked, this, &MainWindow::on_RemoveButton_clicked);

    QObject::connect(CourseButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

    QObject::connect(InstructorButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

    QObject::connect(RoomButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

}


void MainWindow::on_RemoveButton_clicked()
{

    if(departmentCounter < 10)
        if(departmentCounter > 1) {

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

                DepartmentMap.remove(key);

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


void MainWindow::on_ValidateButton_clicked() //currently broken with reliance on backend - 4/17/2023
{

    get_Table_Data();

    int oldConflictCounter = conflictCounter;

    conflictCounter = validateSchedule();

    clear_Table();

    populate_Table(get_File_Data());

    find_Conflicts();

    if(oldConflictCounter != conflictCounter)
        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter));

    if(conflictCounter == 0) {

        scheduleValidated = true;

        ui->ConflictLine->hide();

        ui->ValidateButton->hide();

    }

}


void MainWindow::on_DarkModeAction_triggered()
{

    if(!darkMode) {

        ui->centralWidget->setStyleSheet("QWidget{background: black; border-style: outset; border-color: dimgrey; color: gainsboro;}"
                                         "QPushButton{border-width: 1px; color: white; background-color: dimgrey;}"
                                         "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                         "QLineEdit{border-width:2px; color: gainsboro; background-color: black}"
                                         "QTableWidget{border-color: dimgrey; border-width: 2px; alternate-background-color: dimgrey; gridline-color: white;}"
                                         "QHeaderView::section{background-color: black; color: gainsboro;}"
                                         "QTableCornerButton::section{background-color: black; border-color: dimgray; border-width: 2px;}"
                                         "QMenuBar{background-color: dimgrey; border-style: outset; border-color: dimgrey; color: gainsboro;}"
                                         "QMenu{background-color: black;}");

        ui->menuBar->setStyleSheet("QMenuBar{background-color: dimgrey; border-style: outset; border-color: dimgrey; color: gainsboro;}"
                                   "QMenu{background-color: black;}");

        darkMode = true;

    } else {

        ui->centralWidget->setStyleSheet("QWidget{background: white; border-style: outset; border-color: black; color: black;}"
                                         "QLineEdit{border-width:1px; color: black; background-color: white}"
                                         "QPushButton{border-width: 1px; color: black; background-color: white;}"
                                         "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                         "QPlainTextEdit{border-width: 1px;}"
                                         "QTableWidget{border-color: black; border-width: 1px; alternate-background-color: lightgrey; gridline-color: black;}"
                                         "QHeaderView::section{background-color: white; color: black;}"
                                         "QTableCornerButton::section{background-color: white; border-color: black; border-width: 1px;}"
                                         "QMenuBar{background: white; border-style: outset; border-color: black; color: black;}"
                                         "QMenu{background: white;}");

        ui->menuBar->setStyleSheet("QMenuBar{background: white; border-style: outset; border-color: black; color: black;}"
                                   "QMenu{background: white;}");

        darkMode = false;

    }

}


void MainWindow::display_Generated_Schedule()
{

    if(scheduleHidden) {

        ui->scheduleTable->show();

        scheduleHidden = false;

    }

    if(scheduleGenerated || scheduleValidated) {

        ui->SaveCSVButton->show();

        ui->SavePDFButton->show();

    }

    if(conflictCounter > 0) {

        ui->ValidateButton->show();

        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter));

        ui->ConflictLine->show();

    }

}


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


QStringList MainWindow::get_File_Data()
{

    QStringList rowData;

    QString data;

    QFile file(generatedCSVPath);

    QTextStream stream(&file);

    if(file.open(QFile::ReadOnly)) {

        while(!stream.atEnd()) {

            data = stream.readAll();

            rowData = data.split("\n");

        }

    }

    file.close();

    return rowData;

}


void MainWindow::initialize_Table(int numRows)
{

    auto table = ui->scheduleTable;

    ComboBoxDelegate* comboSecType = new ComboBoxDelegate(table);

    ComboBoxDelegate2* comboDay = new ComboBoxDelegate2(table);

    ComboBoxDelegate3* comboStart = new ComboBoxDelegate3(table);

    ComboBoxDelegate4* comboEnd = new ComboBoxDelegate4(table);

    table->setRowCount(numRows-1); //number of rows -1 to prevent inclusion of header row of csv

    table->setColumnCount(numColumns);

    table->setItemDelegateForColumn(1, comboSecType);

    table->setItemDelegateForColumn(7, comboDay);

    table->setItemDelegateForColumn(8, comboStart);

    table->setItemDelegateForColumn(9, comboEnd);

    table->setColumnCount(numColumns);

    QString headerRow[numColumns] = {"Conflict", "Section Type", "CRN", "Course", "Title", "Credit", "Max Enrollment", "Days", "Start", "End", "Building", "Room", "Instructor"};

    for(int y = 0; y < numColumns; y++) { //columns

        auto item = new QTableWidgetItem;

        item->setText(headerRow[y]);

        table->setHorizontalHeaderItem(y, item);

        for (int x = 0; x < numRows; x++) { //rows

            auto cell = new QTableWidgetItem;

            table->setItem(x, y, cell);

            if (y == 0) {

                cell->setFlags(cell->flags() & ~Qt::ItemIsEnabled);

            }

        }

    }

}


void MainWindow::populate_Table(QStringList rowData)
{

    auto table = ui->scheduleTable;

    QString cellData;

    QStringList cell;

    for (int x = 0; x < rowData.size(); x++) { //columns

        cellData = rowData[x];

        if(x >= 1)
            cell = cellData.split(",");

        for (int y = 0; y < cell.size(); y++) { //rows

            table->item(x-1, y)->setText(cell[y]);

        }

        cellData.clear();

    }

}


void MainWindow::get_Table_Data()
{

    QFile file(generatedCSVPath);

    QTextStream stream(&file);

    if(file.open(QFile::WriteOnly)) {

        auto table = ui->scheduleTable;

        stream << "Conflict,Section Type,CRN,Course,Title,Credit,Max Enrollment,Days,Start,End,Building,Room,Instructor\n";

        for (int x = 0; x < table->rowCount(); x++) {

            for (int y = 0; y < table->columnCount(); y++) {

                stream << table->item(x,y)->text();

                if(y+1 < table->columnCount())
                    stream << ",";

            }

        }

    }

}


void MainWindow::find_Conflicts()
{

    auto table = ui->scheduleTable;

    for (int x = 0; x < table->rowCount(); x++) { //columns

        if(table->item(x, 0)->text() == "TRUE") {

            for (int y = 0; y < table->columnCount(); y++) { //rows

                table->item(x, y)->setBackground(QBrush(QColor("lightcoral")));

            }

        }

    }

}


void MainWindow::clear_Table()
{

    auto table = ui->scheduleTable;

    table->setRowCount(0);

    table->setColumnCount(0);

    scheduleGenerated = false;

    ui->ConflictLine->hide();

    ui->ValidateButton->hide();

    ui->SaveCSVButton->hide();

    ui->SavePDFButton->hide();

}
