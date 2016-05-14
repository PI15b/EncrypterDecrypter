#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T22:28:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Encypter
TEMPLATE = app


SOURCES += main.cpp\
        Encrypter.cpp \
    mainwindow.cpp \
    Rijndael/Rijndael.cpp

HEADERS  += Encrypter.h \
    mainwindow.h \
    Rijndael/Rijndael.h

FORMS    += Encrypter.ui

RESOURCES += \
    enc_resources.qrc
