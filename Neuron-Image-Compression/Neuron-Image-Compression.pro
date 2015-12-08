#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T14:13:50
#
#-------------------------------------------------

QT       += core gui

win32: QT += winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Neuron-Image-Compression
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_AVAILABLE

RC_ICONS += "img/logo.ico"

SOURCES += main.cpp\
        mainwidget.cpp \
    kernel/carray.cpp \
    kernel/cmatrix.cpp \
    kernel/cvector.cpp \
    filenameedit.cpp \
    kernel/crange.cpp \
    pixmapwidget.cpp \
    kernel/csize.cpp \
    framegriddisplay.cpp \
    neuralspan.cpp \
    neuralcompressor.cpp \
    trainingset.cpp \
    trainingsample.cpp

HEADERS  += mainwidget.h \
    kernel/carray.h \
    kernel/cmatrix.h \
    kernel/cvector.h \
    filenameedit.h \
    kernel/crange.h \
    pixmapwidget.h \
    kernel/csize.h \
    framegriddisplay.h \
    neuralspan.h \
    neuralcompressor.h \
    trainingset.h \
    trainingsample.h

RESOURCES += \
    res.qrc
