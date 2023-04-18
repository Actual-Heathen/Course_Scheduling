#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "course.h"
#include "department.h"
#include "engine.h"
#include "instructor.h"
#include "resourceManager.h"
#include "room.h"
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
#include <QPdfWriter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const int numColumns = 13;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString fileStoragePath, generatedCSVPath;

public:

    int departmentCounter, conflictCounter;

    bool populated, darkMode, scheduleGenerated, scheduleValidated, scheduleHidden;

    QStringList keys;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool check_File_Extension(QString filePath);

private slots:

    void on_GenerateButton_clicked(); //grabs filepaths from department(s) and uploads them to array for storage

    void on_SaveCSVButton_clicked();

    void on_SavePDFButton_clicked();

    void on_DepartmentButton_clicked();

    void on_RemoveButton_clicked();

    void on_ValidateButton_clicked();

    void on_DarkModeAction_triggered();

    void display_Generated_Schedule();

    void find_File_Path();

    QStringList get_File_Data();

    void initialize_Table(int numRows);

    void populate_Table(QStringList rowData);

    void get_Table_Data();

    void find_Conflicts();

    void clear_Table();

private:
    Ui::MainWindow *ui;

    QMultiMap<QHBoxLayout*, QWidget*> DepartmentMap;

};
#endif // MAINWINDOW_H
