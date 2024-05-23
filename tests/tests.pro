######################################################################
# Test project file: tests/tests.pro
######################################################################

TEMPLATE = app
TARGET = tests.exe
INCLUDEPATH += ../include

QT += testlib

CONFIG += console c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ..

OBJECTS_DIR = ../build/tests/obj
MOC_DIR = ../build/tests/moc

# Input
HEADERS += TestExample.h

SOURCES += TestExample.cpp

# Include the MOC file
include(../build/moc/testsTestExample.moc)

QMAKE_CXXFLAGS += -fPIC
