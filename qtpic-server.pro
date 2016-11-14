#-------------------------------------------------
#
# Project created by QtCreator 2016-08-28T20:10:43
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = qtp-server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    thread.cpp

HEADERS += \
    server.h \
    thread.h
