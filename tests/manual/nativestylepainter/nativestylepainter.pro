TEMPLATE = app
TARGET = nativestylepainter
QT += core gui gui-private

NATIVESTYLEPATH = ../../../src/imports/controls/nativestylepainter/

INCLUDEPATH += . $$NATIVESTYLEPATH
SOURCES += main.cpp

include($$NATIVESTYLEPATH/nativestylepainter.pri)
