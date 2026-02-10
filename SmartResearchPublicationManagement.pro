QT       += core gui widgets sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++17
TEMPLATE = app
TARGET = SmartResearchPublicationManagement

SOURCES += \
    main.cpp \
    smartresearchpublicationmanagement.cpp

HEADERS += \
    smartresearchpublicationmanagement.h

FORMS += \
    smartresearchpublicationmanagement.ui

RESOURCES += \
    resources.qrc
