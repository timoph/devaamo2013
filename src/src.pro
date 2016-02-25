TEMPLATE = app
TARGET = hackterminal
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = ../bin

QT -= gui
QT += core

CONFIG += console

macx {
    CONFIG -= app_bundle
}

# Input
SOURCES += main.cpp \
    engine.cpp \
    abstractpuzzle.cpp \
    intropuzzle.cpp \
    fallospuzzle.cpp \
    bfpuzzle.cpp \
    asciipuzzle.cpp \
    braillepuzzle.cpp \
    urlpuzzle.cpp \
    adventurepuzzle.cpp \
    whitespacepuzzle.cpp \
    battlepuzzle.cpp \
    shellpuzzle.cpp

HEADERS += \
    engine.h \
    abstractpuzzle.h \
    intropuzzle.h \
    fallospuzzle.h \
    bfpuzzle.h \
    asciipuzzle.h \
    constants.h \
    braillepuzzle.h \
    urlpuzzle.h \
    adventurepuzzle.h \
    whitespacepuzzle.h \
    battlepuzzle.h \
    shellpuzzle.h

unix {
    target.path = /usr/bin/

    INSTALLS += target
}
