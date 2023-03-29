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

    ui->SaveButton->hide();

    ui->PrintButton->hide();

    ui->ConflictLine->hide();

    ui->ValidateButton->hide();

    generatedSchedulePath = "../Course_Scheduling/generatedSchedule.txt";

    fileStoragePath = "../Course_Scheduling/filePathStorage.txt";

    departmentCounter = 1;

    populated = false;

    darkMode = false;

    generated = false;

    validated = false;

    initialize_table(17);

}


MainWindow::~MainWindow()
{

    delete ui;

}


void MainWindow::display_Generated_Schedule()
{

    //ADD EXCEL SPREADSHEET DISPLAY HERE

    if(generated || validated) {

        ui->SaveButton->show();

        ui->PrintButton->show();

        ui->ConflictLine->show();

        generated = false;

        validated = false;

    }

    if(conflictCounter > 0) {

        ui->ValidateButton->show();

        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter));

    }

}


void MainWindow::on_CourseButton_clicked()
{

    QString fileContent;

    QString fileName = QFileDialog::getOpenFileName(this, "Choose File");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {

        //insert error box here

        return;
    }

    QTextStream stream(&file);

    fileContent = stream.readAll();

    file.close();

    ui->CourseLine->setText(fileName);

}


void MainWindow::on_InstructorButton_clicked()
{

    QString fileContent;

    QString fileName = QFileDialog::getOpenFileName(this, "Choose File");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {

        //insert error box here

        return;
    }

    QTextStream stream(&file);

    fileContent = stream.readAll();

    file.close();

    ui->InstructorLine->setText(fileName);

}


void MainWindow::on_RoomsButton_clicked()
{

    QString fileContent;

    QString filePath = QFileDialog::getOpenFileName(this, "Choose File");

    if (filePath.isEmpty())
        return;

    QFile file(filePath);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {

        //insert error box here

        return;
    }

    QTextStream stream(&file);

    fileContent = stream.readAll();

    file.close();

    ui->RoomsLine->setText(filePath);

}


void MainWindow::on_GenerateButton_clicked()
{

    generated = true;

    QString filePath = fileStoragePath;

    QFile file(filePath);

    if(file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {

        QTextStream stream(&file);

        for(int i = 0; i < departmentCounter; i++) {

            stream << ui->DepartmentLine->text() << "\n";

            ui->DepartmentLine->clear();

            stream << ui->CourseLine->text() << "\n";

            ui->CourseLine->clear();

            stream << ui->InstructorLine->text() << "\n";

            ui->InstructorLine->clear();

            stream << ui->RoomsLine->text() << "\n";

            ui->RoomsLine->clear();

        }

        populated = true;

    }

    conflictCounter = resourceManager(populated, departmentCounter, fileStoragePath.toStdString(), generatedSchedulePath.toStdString());

    file.close();

    populated = false;

    display_Generated_Schedule();

}


void MainWindow::on_SaveButton_clicked() //WILL NEED REWORK WITH IMPLEMENTATION OF CSVs
{

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    filePath = filePath + "/schedule.txt";

    QString fileContent = "Place holder until CSV implementation";

    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream stream(&file);

        stream << fileContent;

    }

    file.close();

}


void MainWindow::on_PrintButton_clicked() //WILL NEED REWORK WITH IMPLEMENTATION OF CSVs
{

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    filePath = filePath + "/schedule.txt";

    QString fileContent = "Place holder until CSV implementation";

    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream stream(&file);

        stream << fileContent;

    }

    file.close();

}


void MainWindow::on_DepartmentButton_clicked()
{

    //departmentCounter++; THIS WILL BE ENABLED LATER!!!

}


void MainWindow::on_darkModeAction_triggered() //Needs rework to simplify!!
{

    if(!darkMode) {

        ui->centralWidget->setStyleSheet("QWidget{background: black; border-style: outset; border-color: dimgrey; color: gainsboro;};"
                                         "QLineEdit{border-width:2px; color: gainsboro; background-color: black};");
        ui->scrollAreaWidgetContents->setStyleSheet("QPushButton{border-width: 1px; color: white; background-color: dimgrey;}"
                                                    "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                                    "QPlainTextEdit{border-width: 2px;}");
        ui->inputFrame->setStyleSheet("");
        ui->menuBar->setStyleSheet("background: dimgrey; border-style: outset; border-color: dimgrey; color: gainsboro;");
        ui->menuView->setStyleSheet("background-color: black;");
        ui->scheduleTable->setStyleSheet("QTableWidget{border-color: dimgrey; border-width: 2px;}"
                                         "QHeaderView::section{background-color: black; color: gainsboro;}"
                                         "QTableCornerButton::section{background-color: black; border-color: dimgray; border-width: 2px;}"
                                         "QTableWidget {alternate-background-color: dimgrey; gridline-color: white;}");

        darkMode = true;

    } else {

        ui->centralWidget->setStyleSheet("QWidget{background: white; border-style: outset; border-color: black; color: black;}"
                                         "QLineEdit{border-width:1px; color: black; background-color: white};");
        ui->scrollAreaWidgetContents->setStyleSheet("QPushButton{border-width: 1px; color: black; background-color: white;}"
                                                    "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                                    "QPlainTextEdit{border-width: 1px;}");
        ui->inputFrame->setStyleSheet("");
        ui->menuBar->setStyleSheet("background: white; border-style: outset; border-color: black; color: black;");
        ui->menuView->setStyleSheet("background: white;");
        ui->scheduleTable->setStyleSheet("QTableWidget{border-color: black; border-width: 1px;}"
                                         "QHeaderView::section{background-color: white; color: black;}"
                                         "QTableCornerButton::section{background-color: white; border-color: black; border-width: 1px;}"
                                         "QTableWidget {alternate-background-color: lightgrey; gridline-color: black;}");

        darkMode = false;
    }

}


void MainWindow::initialize_table(int rows)
{

    const int columns = 17;

    auto table = ui->scheduleTable;

    table->setRowCount(rows); //row number will be provided dynamically based on how many departments are scheduled

    table->setColumnCount(columns);

    QString headerRow[columns] = {"Section Type", "CRN", "Course", "Title", "Credit", "Max Enrollment", "Enrolled", "Available", "Wait List", "MTYP", "Days", "Start", "End", "Building", "Room", "Instructor", "Conflict"};

    for(int i = 0; i < columns; i++) {

        auto item = new QTableWidgetItem;

        item->setText(headerRow[i]);

        table->setHorizontalHeaderItem(i, item);

    }

}


void MainWindow::on_ValidateButton_clicked()
{

    validated = true;

    //add function call here to resourceManager to validate changes made to schedule: i.e. create new CSV and scan it, then print it back out

    ui->SaveButton->hide();

    ui->PrintButton->hide();

    ui->ValidateButton->hide();

    display_Generated_Schedule();

}

