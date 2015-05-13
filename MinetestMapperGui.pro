#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T02:49:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinetestMapperGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    minetestmappergui.qrc

TRANSLATIONS = languages/gui_de.ts\
               languages/gui_en.ts

DISTFILES +=
