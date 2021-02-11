#-------------------------------------------------
#
# Project created by QtCreator 2020-03-11T16:04:09
#
#-------------------------------------------------

QT       += core gui widgets
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cyclinfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapeditor.cpp

HEADERS  += mainwindow.h \
    mapeditor.h

TRANSLATIONS = Cyclinfo_fr.ts Cyclinfo_en.ts

FORMS    += mainwindow.ui
