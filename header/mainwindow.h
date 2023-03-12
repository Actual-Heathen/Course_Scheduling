#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString generatedFilePath;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void display_Generated_Schedule(QString& filePath);

private slots:
    void on_CourseButton_clicked();

    void on_InstructorButton_clicked();

    void on_RoomsButton_clicked();

    void on_GenerateButton_clicked(); //grabs filepaths from department(s) and uploads them to array for storage

    void on_SaveButton_clicked();

    void on_PrintButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


// NEED A DEPARTMENT COUNTER TO READ IN EVERY DEPARTMENTS FILES
