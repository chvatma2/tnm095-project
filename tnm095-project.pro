#-------------------------------------------------
#
# Project created by QtCreator 2018-09-28T03:48:30
#
#-------------------------------------------------

QT       += core gui opengl

win64:LIBS += -lOpenGL32

win32:LIBS += -lOpenGL32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tnm095-project
TEMPLATE = app

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    openglwidget.cpp \
    aifileloader.cpp \
    aisubsystem.cpp \
    gameobject.cpp \
    component.cpp \
    characterlistwidget.cpp \
    characterwidget.cpp \
    btnode.cpp \
    btroot.cpp \
    btselector.cpp \
    btsequence.cpp \
    btcondition.cpp \
    btaction.cpp \
    map.cpp \
    positioncomponent.cpp \
    agentcomponent.cpp \
    spritecomponent.cpp \
    rendercomponent.cpp \
    aicomponent.cpp \
    btactionidle.cpp \
    amountcomponent.cpp \
    btrestingaction.cpp \
    btsetdata.cpp \
    btseekingfoodaction.cpp \
    btseektreeaction.cpp \
    btwalkrandom.cpp

HEADERS += \
        mainwindow.h \
    openglwidget.h \
    aifileloader.h \
    aisubsystem.h \
    gameobject.h \
    component.h \
    characterlistwidget.h \
    characterwidget.h \
    btnode.h \
    btroot.h \
    btselector.h \
    btsequence.h \
    btcondition.h \
    btaction.h \
    map.h \
    positioncomponent.h \
    agentcomponent.h \
    spritecomponent.h \
    rendercomponent.h \
    aicomponent.h \
    btactionidle.h \
    amountcomponent.h \
    btrestingaction.h \
    btsetdata.h \
    btseekingfoodaction.h \
    btseektreeaction.h \
    btwalkrandom.h
