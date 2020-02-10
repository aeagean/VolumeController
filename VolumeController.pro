#-------------------------------------------------
#
# Project created by QtCreator 2020-02-03T17:54:11
#
#-------------------------------------------------

QT       += core gui
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VolumeControl
TEMPLATE = app

RC_ICONS = app.ico
LIBS += -lole32

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    VolumeController.cpp

HEADERS += \
        MainWindow.h \
        VolumeController.h

FORMS += \
        MainWindow.ui
