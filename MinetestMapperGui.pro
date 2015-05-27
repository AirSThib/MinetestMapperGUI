#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T02:49:12
#
#-------------------------------------------------

QT       += core gui
win32:QT += winextras

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

#Application version
VERSION_MAJOR = 0
VERSION_MINOR = 4
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

RC_ICONS = images/icon.ico
RC_LANG = 0x0407

QMAKE_TARGET_PRODUCT = "Minetest Mappger GUI"
QMAKE_TARGET_DESCRIPTION = "Graphical user interface for MinetestMapper"
QMAKE_TARGET_COPYRIGHT = "2015 addi; CC BY"
