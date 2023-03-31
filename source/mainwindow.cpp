#include "../header/mainwindow.h"
#include "../ui_mainwindow.h"

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

    generatedSchedulePath = "../Course_Scheduling/generatedSchedule.txt";

    fileStoragePath = "../Course_Scheduling/filePathStorage.txt";

    departmentCounter = 1;

    populated = false;

    darkMode = false;

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display_Generated_Schedule()
{

    QString fileContent;

    QString filePath = generatedSchedulePath;

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

    ui->scheduleText->setPlainText(fileContent);

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

    file.close();

    resourceManager(populated, departmentCounter, fileStoragePath.toStdString(), generatedSchedulePath.toStdString());

    populated = false;

    display_Generated_Schedule();

    ui->SaveButton->show();

    ui->PrintButton->show();


}


void MainWindow::on_SaveButton_clicked()
{

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    filePath = filePath + "/schedule.txt";

    QString fileContent = ui->scheduleText->toPlainText();

    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream stream(&file);

        stream << fileContent;

    }

    file.close();


}


void MainWindow::on_PrintButton_clicked()
{

    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    filePath = filePath + "/schedule.txt";

    QString fileContent = ui->scheduleText->toPlainText();

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


void MainWindow::on_darkModeAction_triggered()
{

    if(!darkMode) {

        ui->centralWidget->setStyleSheet("background: black; border-style: outset; border-color: dimgrey; color: gainsboro;");
        ui->scrollAreaWidgetContents->setStyleSheet("QPushButton{border-width: 1px; color: white; background-color: dimgrey;}"
                                                    "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                                    "QPlainTextEdit{border-width: 2px;}");
        ui->inputFrame->setStyleSheet("QLineEdit{border-width:2px; color: gainsboro; background-color: black};");
        ui->menuBar->setStyleSheet("background: dimgrey; border-style: outset; border-color: dimgrey; color: gainsboro;");
        ui->menuView->setStyleSheet("background: black;");

        darkMode = true;

    } else {

        ui->centralWidget->setStyleSheet("background: white; border-style: outset; border-color: black; color: black;");
        ui->scrollAreaWidgetContents->setStyleSheet("QPushButton{border-width: 1px; color: black; background-color: white;}"
                                                    "QPushButton::Pressed{border-width: 2px; color: gainsboro; background-color: black}"
                                                    "QPlainTextEdit{border-width: 1px;}");
        ui->inputFrame->setStyleSheet("QLineEdit{border-width:1px; color: black; background-color: white};");
        ui->menuBar->setStyleSheet("background: white; border-style: outset; border-color: black; color: black;");
        ui->menuView->setStyleSheet("background: white;");

        darkMode = false;
    }

}

