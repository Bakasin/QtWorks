#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T22:13:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Personal
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        personalmain.cpp \
    failedconnectiondialog.cpp \
    employeeslist.cpp \
    employeeedit.cpp \
    employeesreport.cpp

HEADERS  += personalmain.h \
    failedconnectiondialog.h \
    employeeslist.h \
    employeeedit.h \
    employeesreport.h
