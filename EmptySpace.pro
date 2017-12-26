#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T18:18:24
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmptySpace
TEMPLATE = app
CONFIG += c++11

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
    myapplication.cpp \
    gamewindow.cpp \
    hero.cpp \
    decoration.cpp \
    herothrust.cpp \
    bullet.cpp \
    explosion.cpp \
    gameplaystate.cpp \
    menuscene.cpp \
    settingsstate.cpp \
    settingsscene.cpp \
    bgmusicplayer.cpp \
    quitwindow.cpp \
    mainmenustate.cpp \
    aboutstate.cpp \
    aboutscene.cpp \
    gun.cpp \
    gamescene.cpp \
    gameview.cpp \
    flamestream.cpp \
    state.cpp \
    customtextitem.cpp \
    hpline.cpp \
    minimap.cpp \
    gameplaymovableitem.cpp \
    gameeventofappearing.cpp \
    gameinfoevent.cpp \
    infowindow.cpp \
    enemy.cpp

HEADERS  += \
    myapplication.h \
    gamewindow.h \
    hero.h \
    decoration.h \
    herothrust.h \
    bullet.h \
    project_math.h \
    explosion.h \
    state.h \
    gameplaystate.h \
    menuscene.h \
    settingsstate.h \
    settingsscene.h \
    bgmusicplayer.h \
    sizes.h \
    sounds.h \
    quitwindow.h \
    mainmenustate.h \
    aboutstate.h \
    aboutscene.h \
    gun.h \
    gamescene.h \
    gameview.h \
    gameplayitem.h \
    flamestream.h \
    templates.h \
    customtextitem.h \
    hpline.h \
    minimap.h \
    gameplaymovableitem.h \
    gameevent.h \
    gameeventofappearing.h \
    gameinfoevent.h \
    infowindow.h \
    enemy.h

FORMS    += widget.ui

RESOURCES +=

DISTFILES +=
