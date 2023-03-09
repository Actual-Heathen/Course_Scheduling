#include "../Course_Scheduling/header/course.h"
#include "../Course_Scheduling/header/department.h"
#include "../Course_Scheduling/header/engine.h"
#include "../Course_Scheduling/header/instructor.h"
#include "../Course_Scheduling/header/room.h"
#include "../Course_Scheduling/header/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
