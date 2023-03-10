#include "../header/mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->SaveButton->hide();

    ui->PrintButton->hide();

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display_Generated_Schedule(QString& filePath)
{

    QString fileContent;

    if (filePath.isEmpty())
        return;

    QFile file(filePath);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {

        //insert error box here

        return;
    }

    QTextStream in(&file);

    fileContent = in.readAll();

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

    QTextStream in(&file);

    fileContent = in.readAll();

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

    QTextStream in(&file);

    fileContent = in.readAll();

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

    QTextStream in(&file);

    fileContent = in.readAll();

    file.close();

    ui->RoomsLine->setText(filePath);

}


void MainWindow::on_GenerateButton_clicked()
{

    display_Generated_Schedule(generatedFilePath);

    ui->scheduleText->setPlainText("WIP");

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

