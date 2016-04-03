#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T11:05:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PMCAConfTool
TEMPLATE = app


SOURCES += main.cpp\
        pmcaconf_mainwin.cpp \
    pmcapartlist.cpp

HEADERS  += pmcaconf_mainwin.h \
    pmcapartlist.h

FORMS    += pmcaconf_mainwin.ui

RESOURCES += \
    images.qrc
