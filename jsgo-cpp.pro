#-------------------------------------------------
#
# Project created by QtCreator 2017-02-17T15:05:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = jsgo-cpp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Lib.cpp \
    JS.cpp

HEADERS += \
    Lib.h \
    JS.h

QMAKE_CXXFLAGS += -std=c++11
QT += script
