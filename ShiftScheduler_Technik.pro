QT += core
QT -= gui
QT += xlsx

CONFIG += c++11

TARGET = ShiftScheduler_Technik
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/plan.cpp \
    src/technician.cpp \
    src/shifttable.cpp


HEADERS += \
    src/global.h \
    src/plan.h \
    src/technician.h \
    src/shifttable.h
