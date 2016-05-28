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
        Encypter.cpp \
    Rijndael/aes.cpp \
    encrypt.cpp

HEADERS  += Encypter.h \
    Rijndael/aes.h \
    encrypt.h

FORMS    += Encypter.ui

RESOURCES += \
    enc_resources.qrc

QMAKE_CXXFLAGS += -std=c++11

LIBS += -L$$PWD/open-ssl/lib -lcrypto -lssl

INCLUDEPATH += /home/fuxy/EncrypterDecrypter/EncrypterDecrypter/open-ssl/include
