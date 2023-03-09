#include "header/course.h"
#include "header/department.h"
#include "header/engine.h"
#include "header/instructor.h"
#include "header/room.h"
#include "header/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
