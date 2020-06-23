#-------------------------------------------------
#
# Project created by QtCreator 2020-05-23T13:44:40
#
#-------------------------------------------------

QT       += core gui
QT       += multimediawidgets
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaFangZuoYe
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
    buttonclass.cpp \
    intropage.cpp \
    towerclass.cpp \
    easymode.cpp \
    hardmode.cpp \
    waypoint.cpp \
    enemyclass.cpp \
    gamebase.cpp

HEADERS += \
        mainwindow.h \
    buttonclass.h \
    intropage.h \
    towerclass.h \
    easymode.h \
    hardmode.h \
    waypoint.h \
    enemyclass.h \
    gamebase.h \
    unity.h\

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc




