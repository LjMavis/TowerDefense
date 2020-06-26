#-------------------------------------------------
#
# Project created by QtCreator 2020-05-27T21:50:10
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia #为了使用QMediaPlayer
#为了解决no such slot
#OBJECTS_DIR  = tmp
#MOC_DIR      = tmp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mybutton.cpp \
    chooselevel.cpp \
    playscene.cpp \
    towerposition.cpp \
    waypoint.cpp \
    bullet.cpp \
    towerparent.cpp \
    towerfreeze.cpp \
    ice.cpp \
    towerall.cpp \
    all.cpp \
    enemy.cpp \
    intro.cpp

HEADERS += \
        mainwindow.h \
    mybutton.h \
    chooselevel.h \
    playscene.h \
    towerposition.h \
    waypoint.h \
    bullet.h \
    towerparent.h \
    towerfreeze.h \
    ice.h \
    towerall.h \
    all.h \
    enemy.h \
    intro.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc




