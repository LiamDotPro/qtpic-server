QT += core network sql

CONFIG += c++11

TARGET = qtpic-server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    mserver.cpp \
    savetask.cpp

HEADERS += \
    client.h \
    mserver.h \
    savetask.h
