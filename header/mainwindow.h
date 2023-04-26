#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "resourceManager.h"
#include "comboboxDelegate.h"
#include "comboboxDelegate2.h"
#include "comboboxDelegate3.h"
#include "comboboxDelegate4.h"

#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>
#include <string>
#include <fstream>
#include <QStyledItemDelegate>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const int numColumns = 13; //constant to determine number of columns for the table

class MainWindow : public QMainWindow
{

    Q_OBJECT

    QString fileStoragePath, generatedCSVPath; //static file path storage

public:

    int departmentCounter, conflictCounter; //gui counters

    bool populated, darkMode, scheduleGenerated, scheduleValidated, scheduleHidden; //gui bool checks

    MainWindow(QWidget *parent = nullptr); //Constructor for MainWindow

    ~MainWindow(); //Deconstructor for MainWindow

    bool check_File_Extension(QString filePath); //Check to make sure the inputted department file is a csv

    bool check_Department_Acronym(QString departmentAcronym); //Check to make sure the inputted department acronym is valid

private slots:

    void on_GenerateButton_clicked(); //Grabs all the filepaths and department names from department inputs and stores them in the a local .txt file for backend use, then accesses the output.csv via additional called functions to display the schedule

    void on_SaveCSVButton_clicked(); //Save the generated schedule as a csv while notifying the user of any existing conflicts

    void on_SaveTXTButton_clicked(); //Save the generated schedule as a txt while notifying the user of any existing conflicts

    void on_DepartmentButton_clicked(); //Generate a new row of department inputs

    void on_RemoveButton_clicked(); //Remove department layout if corresponding remove button is clicked

    void on_ValidateButton_clicked(); //Validate the schedule pulled from schedule widget

    void on_DarkModeAction_triggered(); //Swap interface between darkmode and lightmode stylesheets

    void display_Generated_Schedule(); //Displays necessary schedule/ui info to user

    void find_File_Path(); //Allows user to select file for selected department file input

    QStringList get_File_Data(); //Grabs and returns schedule data from output.csv

    void initialize_Table(int numRows); //Create the Table Widget

    void populate_Table(QStringList rowData); //Populate the Table Widget with generated schedule

    void get_Table_Data(); //Grab data from table widget and store it in output.csv

    void find_Conflicts(); //Iterates through every row in column 0 (conflict column) and checks to see if the row needs to be red to signify conflict

    void clear_Table(); //Clears the table and hides gui buttons and interactions

    void on_actionAdd_Department_triggered(); //Menu button to add department

    void on_actionGenerate_Schedule_triggered(); //Menu button to generate schedule

    void on_actionValidate_Schedule_triggered(); //Menu button to validate schedule

    void on_actionSave_as_CSV_triggered(); //Menu button to save schedule as csv

    void on_actionSave_to_Print_triggered(); //Menu button to save schedule as txt

    void on_actionLegend_triggered(); //Menu button to display legend describing schedule info

private:

    Ui::MainWindow *ui;

    QMultiMap<QHBoxLayout*, QWidget*> DepartmentMap; //Map used to store department input layouts

};
#endif // MAINWINDOW_H
