#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T18:18:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmptySpace
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
    customscene.cpp \
    myapplication.cpp \
    gamewindow.cpp \
    hero.cpp \
    decoration.cpp \
    herothrust.cpp \
    bullet.cpp \
    explosion.cpp

HEADERS  += \
    customscene.h \
    myapplication.h \
    gamewindow.h \
    hero.h \
    decoration.h \
    herothrust.h \
    direction.h \
    bullet.h \
    project_math.h \
    explosion.h

FORMS    += widget.ui

RESOURCES +=
