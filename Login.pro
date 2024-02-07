QT       += core gui
QT       += sql
QT       += core gui multimedia multimediawidgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QT += printsupport
QT += core gui charts
QT += serialport
QT += network

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MYarduino.cpp \
    QrCode.cpp \
    account.cpp \
    calendar.cpp \
    cameramanager.cpp \
    clients.cpp \
    collecte.cpp \
    connection.cpp \
    employe.cpp \
    forgot.cpp \
    main.cpp \
    main_page.cpp \
    mainwindow.cpp \
    newacc.cpp \
    newpwd.cpp \
    produit.cpp \
    smtp.cpp


HEADERS += \
    MYarduino.h \
    QrCode.hpp \
    account.h \
    calendar.h \
    cameramanager.h \
    clients.h \
    collecte.h \
    connection.h \
    employe.h \
    forgot.h \
    main_page.h \
    mainwindow.h \
    newacc.h \
    newpwd.h \
    produit.h \
    smtp.h


FORMS += \
    forgot.ui \
    main_page.ui \
    mainwindow.ui \
    newacc.ui \
    newpwd.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
