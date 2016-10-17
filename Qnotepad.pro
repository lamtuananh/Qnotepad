#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T08:04:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qnotepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mywindow.cpp

HEADERS  += mainwindow.h \
    mywindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    appresources.qrc
