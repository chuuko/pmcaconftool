#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T11:05:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PMCAConfTool
TEMPLATE = app dialog

CONFIG += c++11

QMAKE_CXXFLAGS += -fpermissive

SOURCES += sources/main.cpp \
    sources/matedit.cpp \
    sources/pmcaconf_mainwin.cpp \
    sources/pmcapartlist.cpp

HEADERS  += sources/matedit.h \
    sources/pmcaconf_mainwin.h \
    sources/pmcapartlist.h

FORMS    += sources/pmcaconf_mainwin.ui \
    sources/matedit.ui

RESOURCES += \
    images.qrc
