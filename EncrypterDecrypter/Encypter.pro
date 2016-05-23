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
    Rijndael/Rijndael.cpp \
    Rijndael/aes.cpp

HEADERS  += Encrypter.h \
    Rijndael/Rijndael.h \
    Rijndael/aes.h

FORMS    += Encrypter.ui

RESOURCES += \
    enc_resources.qrc

QMAKE_CXXFLAGS += -std=c++11
CONFIG += -mx32
