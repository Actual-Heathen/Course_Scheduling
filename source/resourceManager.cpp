#include "../header/mainwindow.h"
#include "../headers/course.h"
#include "../headers/department.h"
#include "../headers/engine.h"
#include "../headers/instructor.h"
#include "../headers/resourceManager.h"
#include "../headers/room.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
