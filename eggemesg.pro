#-------------------------------------------------
#
# Project created by QtCreator 2018-01-03T12:14:42
#
#-------------------------------------------------

QT       += core core-private gui widgets network websockets

TARGET = eggemesg
TEMPLATE = app

CONFIG += c++17

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
    connectionlistdialog.cpp \
    contacts.cpp \
    main.cpp \
    pwdialog.cpp \
    eggecrypt.cpp \
    connectdialog.cpp \
    mainwindow.cpp \
    debugprint.cpp \
    cryptodialog.cpp \
    curlpost.cpp \
    pwhash.cpp \
    tabdialog.cpp \
    torprocess.cpp \
    userdata.cpp \
    websocketclient.cpp \
    websocketserver.cpp

HEADERS += \
    connectionlistdialog.h \
    contacts.h \
    pwdialog.h \
    eggecrypt.h \
    connectdialog.h \
    mainwindow.h \
    pwhash.h \
    tabdialog.h \
    userdata.h \
    debugprint.h \
    cryptodialog.h \
    curlpost.h \
    version.h \
    torprocess.h \
    websocketclient.h \
    websocketserver.h

FORMS += \
    pwdialog.ui \
    connectdialog.ui \
    mainwindow.ui \
    cryptodialog.ui

unix:!macx: LIBS += -L/opt/Qt/6.9.3/gcc_64/lib -L/usr/local/lib/ -L/usr/lib/x86_64-linux-gnu -lgcrypt \
                    -lgpg-error
unix:!macx: LIBS += -L/usr/local/lib/ -lcurl
unix:!macx: LIBS += -L/usr/lib/ -L/usr/local/lib -lQt6WebSockets -lsodium


INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

INCLUDEPATH += /usr/inluce/x86_64-linux-gnu
INCLUDEPATH += /usr/include/c++/6

DEPENDPATH += /usr/include/x86_64-linux-gnu

DISTFILES +=

RESOURCES += \
    resources.qrc
