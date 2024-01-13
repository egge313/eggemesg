#-------------------------------------------------
#
# Project created by QtCreator 2018-01-03T12:14:42
#
#-------------------------------------------------

QT       += core gui network httpserver

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06500    # disables all the APIs deprecated before Qt 6.5.0


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
    eggehttpserver.cpp

HEADERS += \
    pwdialog.h \
    eggecrypt.h \
    connectdialog.h \
    mainwindow.h \
    serverctrl.h \
    userdata.h \
    debugprint.h \
    cryptodialog.h \
    fortuneserver.h \
    fortunethread.h \
    curlpost.h \
    version.h \
    torprocess.h \
    eggehttpserver.h

FORMS += \
    pwdialog.ui \
    connectdialog.ui \
    mainwindow.ui \
    cryptodialog.ui

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lgcrypt \
                    -lgpg-error
unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lcurl

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

DISTFILES +=

RESOURCES += \
    resources.qrc
