#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "course.h"
#include "department.h"
#include "engine.h"
#include "instructor.h"
#include "resourceManager.h"
#include "room.h"

#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>
#include <string>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString generatedSchedulePath;

    QString fileStoragePath;

public:

    int departmentCounter, conflictCounter;

    bool populated, darkMode, generated, validated;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void display_Generated_Schedule();

private slots:
    void on_CourseButton_clicked();

    void on_InstructorButton_clicked();

    void on_RoomsButton_clicked();

    void on_GenerateButton_clicked(); //grabs filepaths from department(s) and uploads them to array for storage

    void on_SaveButton_clicked();

    void on_PrintButton_clicked();

    void on_DepartmentButton_clicked();

    void on_darkModeAction_triggered();

    void initialize_table(int rows);

    void on_ValidateButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


// NEED A DEPARTMENT COUNTER TO READ IN EVERY DEPARTMENTS FILES
