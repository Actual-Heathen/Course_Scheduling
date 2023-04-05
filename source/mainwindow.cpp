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

    ui->SaveButton->hide();

    ui->PrintButton->hide();

    ui->ConflictLine->hide();

    ui->ValidateButton->hide();

    fileStoragePath = "../Course_Scheduling/filePathStorage.txt";

    generatedCSVPath = "../Course_Scheduling/schedule.csv";

    departmentCounter = 0;

    populated = false;

    darkMode = false;

    scheduleGenerated = false;

    scheduleValidated = false;

}


MainWindow::~MainWindow()
{

    delete ui;

}


void MainWindow::on_GenerateButton_clicked() //Edit later to read from the generated file from backend
{

    scheduleGenerated = true;

    QStringList rowData;

    QString data;

    QString filePath = fileStoragePath;

    QFile file(filePath);

    QTextStream stream(&file);

    if(file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {

        QMap<QWidget*, QHBoxLayout*>::iterator index;

        for(index = DepartmentLayoutMap.begin(); index != DepartmentLayoutMap.end(); index++) {

            QHBoxLayout* DepartmentLayout = DepartmentLayoutMap.value(index.key());

            QWidget* Widget = DepartmentLayout->itemAt(1)->widget();

            QLineEdit* DepartmentName = qobject_cast<QLineEdit*>(Widget);

            Widget = DepartmentLayout->itemAt(3)->widget();

            QLineEdit* CourseFile = qobject_cast<QLineEdit*>(Widget);

            Widget = DepartmentLayout->itemAt(5)->widget();

            QLineEdit* InstructorFile = qobject_cast<QLineEdit*>(Widget);

            Widget = DepartmentLayout->itemAt(7)->widget();

            QLineEdit* RoomFile = qobject_cast<QLineEdit*>(Widget);

            if(!DepartmentName->text().isEmpty())
                stream << DepartmentName->text() << "\n";

            if(!CourseFile->text().isEmpty())
                stream << CourseFile->text() << "\n";

            if(!InstructorFile->text().isEmpty())
                stream << InstructorFile->text() << "\n";

            if(!RoomFile->text().isEmpty())
                stream << RoomFile->text() << "\n";

            index++;
            index++;
            index++;

        }

        populated = true;

    }

    conflictCounter = resourceManager(populated, departmentCounter, fileStoragePath.toStdString());

    file.close();

    rowData = get_File_Data();

    initialize_Table(rowData.size());

    populate_Table(rowData);

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
    ui->GenerateButton->show();

    departmentCounter++;

    ui->DepartmentFrame->setFixedSize(ui->DepartmentFrame->width(), ui->DepartmentFrame->height()+40);

    QVBoxLayout* Layout = qobject_cast<QVBoxLayout*>(ui->additionalDepartmentLayout->layout());

    QHBoxLayout* DepartmentLayout = new QHBoxLayout(ui->DepartmentFrame);

    QPushButton* RemoveButton = new QPushButton(("Remove Department"), ui->DepartmentFrame);

    QPushButton* CourseButton = new QPushButton("Choose File", ui->DepartmentFrame);

    QPushButton* InstructorButton = new QPushButton("Choose File", ui->DepartmentFrame);

    QPushButton* RoomButton = new QPushButton("Choose File", ui->DepartmentFrame);

    QLineEdit* DepartmentLine = new QLineEdit(ui->DepartmentFrame);

    QLineEdit* CourseLine = new QLineEdit(ui->DepartmentFrame);

    QLineEdit* InstructorLine = new QLineEdit(ui->DepartmentFrame);

    QLineEdit* RoomLine = new QLineEdit(ui->DepartmentFrame);

    DepartmentLayout->addWidget(RemoveButton);

    DepartmentLayout->addWidget(DepartmentLine);

    DepartmentLayout->addWidget(CourseButton);

    DepartmentLayout->addWidget(CourseLine);

    DepartmentLayout->addWidget(InstructorButton);

    DepartmentLayout->addWidget(InstructorLine);

    DepartmentLayout->addWidget(RoomButton);

    DepartmentLayout->addWidget(RoomLine);

    Layout->insertLayout(0, DepartmentLayout);

    DepartmentLayoutMap.insert(RemoveButton, DepartmentLayout);

    DepartmentLayoutMap.insert(CourseButton, DepartmentLayout);

    DepartmentLayoutMap.insert(InstructorButton, DepartmentLayout);

    DepartmentLayoutMap.insert(RoomButton, DepartmentLayout);

    QObject::connect(RemoveButton, &QPushButton::clicked, this, &MainWindow::on_RemoveButton_clicked);

    QObject::connect(CourseButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

    QObject::connect(InstructorButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

    QObject::connect(RoomButton, &QPushButton::clicked, this, &MainWindow::find_File_Path);

}


void MainWindow::on_RemoveButton_clicked()
{

    departmentCounter--;

    QPushButton* RemoveButton = qobject_cast<QPushButton*>(sender());

    QHBoxLayout* DepartmentLayout = DepartmentLayoutMap.value(RemoveButton);

    while (DepartmentLayout->count() != 0) {

        QLayoutItem* Item = DepartmentLayout->takeAt(0);

        delete Item->widget();

        delete Item;

    }

    //delete DepartmentLayout;

    //DepartmentLayoutMap.remove(RemoveButton); //NEED TO REWORK TO PROPERLY DELETE FILES INDEXES MAP

    QMap<QWidget*, QHBoxLayout*>::iterator i = DepartmentLayoutMap.begin(); //this might fix it, will need to delete the RemoveButton key, but also every other button that was linked to the layout (thus removing 4 things not just 1)

    while (i != DepartmentLayoutMap.end()) {

        QMap<QWidget*, QHBoxLayout*>::iterator prev = i;

        ++i;

        if (prev.key())
            DepartmentLayoutMap.erase(prev);

    }

}


void MainWindow::on_ValidateButton_clicked()
{

    int newConflictCounter = validateSchedule();

    if(conflictCounter != newConflictCounter) {

        conflictCounter = newConflictCounter;

        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter));

        clear_Table();

        scheduleValidated = true;

        //add function call here to resourceManager to validate changes made to schedule: i.e. create new CSV and scan it, then print it back out

        ui->SaveButton->hide();

        ui->PrintButton->hide();

        ui->ValidateButton->hide();

        populate_Table(get_File_Data());

        display_Generated_Schedule();

    }

}


void MainWindow::on_DarkModeAction_triggered() //Needs rework to simplify!!
{

    if(!darkMode) {

        ui->centralWidget->setStyleSheet("QWidget{background: black; border-style: outset; border-color: dimgrey; color: gainsboro;};"
                                         "QLineEdit{border-width:2px; color: gainsboro; background-color: black};");
        ui->scrollAreaWidgetContents->setStyleSheet("QPushButton{border-width: 1px; color: white; background-color: dimgrey;}"
                                                    "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                                    "QPlainTextEdit{border-width: 2px;}");
        ui->menuBar->setStyleSheet("background: dimgrey; border-style: outset; border-color: dimgrey; color: gainsboro;");
        ui->menuView->setStyleSheet("background-color: black;");
        ui->scheduleTable->setStyleSheet("QTableWidget{border-color: dimgrey; border-width: 2px; alternate-background-color: dimgrey; gridline-color: white;}"
                                         "QHeaderView::section{background-color: black; color: gainsboro;}"
                                         "QTableCornerButton::section{background-color: black; border-color: dimgray; border-width: 2px;}");

        darkMode = true;

    } else {

        ui->centralWidget->setStyleSheet("QWidget{background: white; border-style: outset; border-color: black; color: black;}"
                                         "QLineEdit{border-width:1px; color: black; background-color: white};");
        ui->scrollAreaWidgetContents->setStyleSheet("QPushButton{border-width: 1px; color: black; background-color: white;}"
                                                    "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                                    "QPlainTextEdit{border-width: 1px;}");
        ui->menuBar->setStyleSheet("background: white; border-style: outset; border-color: black; color: black;");
        ui->menuView->setStyleSheet("background: white;");
        ui->scheduleTable->setStyleSheet("QTableWidget{border-color: black; border-width: 1px; alternate-background-color: lightgrey; gridline-color: black;}"
                                         "QHeaderView::section{background-color: white; color: black;}"
                                         "QTableCornerButton::section{background-color: white; border-color: black; border-width: 1px;}");

        darkMode = false;
    }

}


void MainWindow::display_Generated_Schedule() //Needs rework to display proper logic
{
    if(scheduleHidden) {

        ui->scheduleTable->show();

        scheduleHidden = false;

    }

    if(scheduleGenerated || scheduleValidated) {

        ui->SaveButton->show();

        ui->PrintButton->show();

        ui->ConflictLine->show();

        scheduleGenerated = false;

        scheduleValidated = false;

    }

    if(conflictCounter > 0) {

        ui->ValidateButton->show();

        ui->ConflictLine->setText(QString("Conflicts: %1").arg(conflictCounter));

    }

}


void MainWindow::find_File_Path()
{

    QPushButton* FileButton1 = qobject_cast<QPushButton*>(sender());

    QHBoxLayout* DepartmentLayout = DepartmentLayoutMap.value(FileButton1);

    for(int i = 0; i < DepartmentLayout->count(); i++) {

        QWidget* Widget = DepartmentLayout->itemAt(i)->widget();

        QPushButton* FileButton2 = qobject_cast<QPushButton*>(Widget);

        if (FileButton1 == FileButton2) {

            QWidget* Widget2 = DepartmentLayout->itemAt(i+1)->widget();

            QLineEdit* LineEdit = qobject_cast<QLineEdit*>(Widget2);

            QString filePath = QFileDialog::getOpenFileName(this, "Choose File");

            QFile file(filePath);

            if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {

                LineEdit->setText("File Not Found!");

            }else {

                LineEdit->setText(filePath);

            }

            file.close();

            i = DepartmentLayout->count();

        }

    }

}


QStringList MainWindow::get_File_Data()
{

    QStringList rowData;

    QString data;

    QString filePath = generatedCSVPath;

    QFile file(filePath);

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

    table->setRowCount(numRows-1); //number of rows -1 to prevent inclusion of header row of csv

    table->setColumnCount(numColumns);

    QString headerRow[numColumns] = {"Conflict", "Section Type", "CRN", "Course", "Title", "Credit", "Max Enrollment", "Days", "Start", "End", "Building", "Room", "Instructor", };

    for(int y = 0; y < numColumns; y++) { //columns

        auto item = new QTableWidgetItem;

        item->setText(headerRow[y]);

        table->setHorizontalHeaderItem(y, item);

        for (int x = 0; x < numRows; x++) { //rows

            auto cell = new QTableWidgetItem;

            table->setItem(x, y, cell);

        }

    }

}


void MainWindow::populate_Table(QStringList rowData)
{

    auto table = ui->scheduleTable;

    QString cellData;

    QStringList cell;

    for (int x = 0; x < rowData.size(); x++) { //rows

        cellData = rowData[x];

        if(x >= 1)
            cell = cellData.split(",");

        for (int y = 0; y < cell.size(); y++) { //columns

            //QTableWidgetItem *item = new QTableWidgetItem();

            //item->setText(cellData[x]);

            table->item(x-1, y)->setText(cell[y]);

        }

        cellData.clear();

    }

}


void MainWindow::clear_Table()
{

    auto table = ui->scheduleTable;

    for (int x = 0; x < table->rowCount(); x++) {

        for (int y = 0; y < table->columnCount(); y++) {

            table->item(x, y)->setText(NULL);

        }

    }

}
