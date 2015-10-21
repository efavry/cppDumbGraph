TEMPLATE = app
CONFIG += console
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graph.cpp \
    node.cpp

HEADERS += \
    graph.h \
    node.h \
    includecentral.h \
    matrixreader.h

