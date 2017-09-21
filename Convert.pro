#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T11:36:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Convert
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    floathex.cpp \
    asc.cpp \
    scale.cpp

HEADERS  += widget.h \
    floathex.h \
    asc.h \
    scale.h

RC_FILE = conversion.rc
