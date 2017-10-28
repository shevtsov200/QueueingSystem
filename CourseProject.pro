#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T17:46:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Request.cpp \
    Controller.cpp \
    Server.cpp \
    Client.cpp \
    Manager.cpp \
    Buffer.cpp

HEADERS  += mainwindow.h \
    Request.h \
    Controller.h \
    Server.h \
    Client.h \
    Manager.h \
    Buffer.h

FORMS    += mainwindow.ui
