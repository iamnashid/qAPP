
QT += widgets

TEMPLATE = app
TARGET = qAPP
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += json.hpp
SOURCES += main.cpp parser.cpp interfaces.cpp

CONFIG += c++11
LIBS += -lcurl
