#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T22:28:20
#
#-------------------------------------------------

QT       += core gui

LIBS += -LC:/OpenSSL-Win32/lib -llibeay32
INCLUDEPATH += C:/OpenSSL-Win32/include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Encypter
TEMPLATE = app


SOURCES += main.cpp\
        Encrypter.cpp \
    Rijndael/aes.cpp \
    Rijndael/Rijndael.cpp \
    encrypt.cpp

HEADERS  += Encrypter.h \
    settings.h \
    Rijndael/aes.h \
    Rijndael/Rijndael.h \
    encrypt.h

FORMS    += Encrypter.ui

RESOURCES += \
    enc_resources.qrc

QMAKE_CXXFLAGS += -std=c++11
