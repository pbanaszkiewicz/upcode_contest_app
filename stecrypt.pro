#-------------------------------------------------
#
# Project created by QtCreator 2011-01-24T22:34:08
#
#-------------------------------------------------

QT       += core gui

TARGET = stecrypt
TEMPLATE = app

TRANSLATIONS += stecrypt_pl.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    rendervideoframe.cpp \
    xorimage.cpp

HEADERS  += mainwindow.h \
    rendervideoframe.h \
    xorimage.h

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += opencv
