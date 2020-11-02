
QT += widgets

TEMPLATE = app
TARGET = qapp
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += json.hpp
SOURCES += main.cpp parser.cpp interfaces.cpp audio_stream.cpp

CONFIG += c++11
LIBS += -lcurl -lmpg123 -lao
