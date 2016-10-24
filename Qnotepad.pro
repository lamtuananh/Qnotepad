#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T08:04:56
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qnotepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        mywindow.cpp \
    mytextedit.cpp \
    mysyntaxhighlighter.cpp

HEADERS  += mainwindow.h \
        mywindow.h \
    mytextedit.h \
    mysyntaxhighlighter.h

FORMS    += mainwindow.ui

RESOURCES += \
    appresources.qrc
