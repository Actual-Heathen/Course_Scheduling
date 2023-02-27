#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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



}

