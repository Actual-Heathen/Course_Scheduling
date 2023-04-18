QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = uah.ico

SOURCES += \
    source/comboboxDelegate.cpp \
    source/comboboxDelegate2.cpp \
    source/comboboxDelegate3.cpp \
    source/comboboxDelegate4.cpp \
    source/course.cpp \
    source/dayTime.cpp \
    source/department.cpp \
    source/engine.cpp \
    source/instructor.cpp \
    source/resourceManager.cpp \
    source/mainwindow.cpp \
    source/room.cpp
    source/course.cpp
    source/department.cpp
    source/engine.cpp
    source/instructor.cpp
    source/room.cpp
    source/resourceManager.cpp
    source/sanitizer.cpp

HEADERS += \
    header/comboboxDelegate.h \
    header/comboboxDelegate2.h \
    header/comboboxDelegate3.h \
    header/comboboxDelegate4.h \
    header/course.h \
    header/dayTime.h \
    header/department.h \
    header/engine.h \
    header/instructor.h \
    header/mainwindow.h \
    header/resourceManager.h \
    header/room.h
    header/resourceManager.h
    header/department.h
    header/engine.h
    header/instructor.h
    header/room.h
    header/course.h
    header/sanitizer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    filePathStorage.txt \
    schedule.csv \
    schedule.xlsx \
    uah.ico
