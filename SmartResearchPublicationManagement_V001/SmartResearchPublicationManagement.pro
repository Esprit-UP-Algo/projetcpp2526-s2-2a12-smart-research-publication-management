QT       += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++17
TEMPLATE = app
TARGET = SmartResearchPublicationManagement

SOURCES += \
    logindialog.cpp \
    main.cpp \
    smartresearchpublicationmanagement.cpp

HEADERS += \
    logindialog.h \
    smartresearchpublicationmanagement.h

FORMS += \
    logindialog.ui \
    smartresearchpublicationmanagement.ui

RESOURCES += \
    resources.qrc \
    resources.qrc
