#-------------------------------------------------
#
# Project created by QtCreator 2018-01-03T12:14:42
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = eggemesg
TEMPLATE = app

CONFIG += c++20

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06900    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    pwdialog.cpp \
    eggecrypt.cpp \
    connectdialog.cpp \
    mainwindow.cpp \
    debugprint.cpp \
    cryptodialog.cpp \
    fortuneserver.cpp \
    fortunethread.cpp \
    curlpost.cpp \
    torprocess.cpp \
    websocketserver.cpp

HEADERS += \
    pwdialog.h \
    eggecrypt.h \
    connectdialog.h \
    mainwindow.h \
    userdata.h \
    debugprint.h \
    cryptodialog.h \
    fortuneserver.h \
    fortunethread.h \
    curlpost.h \
    version.h \
    torprocess.h \
    websocketserver.h

FORMS += \
    pwdialog.ui \
    connectdialog.ui \
    mainwindow.ui \
    cryptodialog.ui

unix:!macx: LIBS += -L/usr/local/lib/ -L/usr/lib/x86_64-linux-gnu -lgcrypt \
                    -lgpg-error
unix:!macx: LIBS += -L/usr/local/lib/ -lcurl
unix:!macx: LIBS += -L/usr/lib/ -L/usr/local/lib -lQt6WebSockets


INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

INCLUDEPATH += /usr/inluce/x86_64-linux-gnu
INCLUDEPATH += /usr/include/c++/6

DEPENDPATH += /usr/include/x86_64-linux-gnu

DISTFILES +=

RESOURCES += \
    resources.qrc
