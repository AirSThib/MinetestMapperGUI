#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T02:49:12
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5) {
    error(Your Qt version $$QT_VERSION is not supported. Upgrade to Qt5.)
}


QT       += core gui widgets
win32:QT += winextras


TARGET = MinetestMapperGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colorlineedit.cpp \
    geometry.cpp \
    geometrywidget.cpp \
    configdialog.cpp \
    colorstxtassistant.cpp \
    makecolors.cpp \
    drawmapfigure.cpp \
    drawmapfiguretablemodel.cpp \
    figuredelegate.cpp \
    minetestmapperexe.cpp


HEADERS  += mainwindow.h \
    colorlineedit.h \
    geometry.h \
    geometrywidget.h \
    configdialog.h \
    colorstxtassistant.h \
    makecolors.h \
    drawmapfigure.h \
    drawmapfiguretablemodel.h \
    figuredelegate.h \
    minetestmapperexe.h

FORMS    += mainwindow.ui \
    geometrywidget.ui \
    configdialog.ui \
    colorstxtassistant.ui

RESOURCES += \
    minetestmappergui.qrc

TRANSLATIONS = translations/gui_de.ts\
               translations/gui_en.ts

CONFIG += c++11

GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
#something like 0.4.2-55-g123c456
isEmpty(GIT_VERSION) {
    GIT_VERSION = 0.7.0
}
# Turns describe output like 0.4.2-55-g652c397 into "0.4.2.55.123c456"
GIT_VERSION ~= s/v/""
GIT_VERSION ~= s/-/"."
GIT_VERSION ~= s/g/""

DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

VERSION = $$GIT_VERSION
win32 {
    VERSION ~= s/\.[a-f0-9]{6,}//
    #something like 0.4.2.55
}

RC_ICONS = images/icon.ico
RC_LANG = 0x04b0

QMAKE_TARGET_PRODUCT = "Minetest Mappger GUI"
QMAKE_TARGET_DESCRIPTION = "Graphical user interface for MinetestMapper"
QMAKE_TARGET_COPYRIGHT = "2015-2017 addi; CC BY"

win32:contains(QT_ARCH, i386) {
    # Support for x32 Windows XP (Windows 5.01)
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
}
