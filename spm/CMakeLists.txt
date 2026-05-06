cmake_minimum_required(VERSION 3.16)

project(SmartResearchPublicationManagement VERSION 0.1 LANGUAGES CXX)

# --- CONFIGURATION AUTOMATIQUE QT ---
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Correctif pour les chemins longs sous Windows
set(CMAKE_AUTOGEN_BUILD_DIR "C:/tmp/srpm_autogen")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- RECHERCHE DES PACKAGES ---
# Qt6
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql
    Charts
    Network
    Multimedia
    MultimediaWidgets
    SerialPort
    Pdf
)

set(OpenCV_DIR "C:/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/x64/mingw/lib")
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_INCLUDE_DIRS})
# --- LISTE DES SOURCES ---
# On inclut les .cpp et les .h pour qu'ils apparaissent dans l'arborescence de l'IDE
set(PROJECT_SOURCES
    # Fichiers principaux
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    # Dialogues et Auth
    logindialog.cpp
    logindialog.h
    logindialog.ui
    faceauth.cpp
    faceauth.h

    # Modules métier
    connection.cpp
    connection.h
    finance.cpp
    finance.h
    publication.cpp
    publication.h
    employe.cpp
    employe.h
    labs.cpp
    labs.h
    inventory.cpp
    inventory.h
    projet.cpp
    projet.h

    # Utilitaires et Matériel
    session.h
    currencyconverter.cpp
    currencyconverter.h
    ocrscanner.cpp
    ocrscanner.h
    mailsender.cpp
    mailsender.h
    arduino.cpp
    arduino.h
    rfidhandler.cpp
    rfidhandler.h
    smssender.cpp
    smssender.h
    labsexporter.cpp
    labsexporter.h

    # Cartographie
    mapdialog.cpp
    mapdialog.h
    tilemapwidget.cpp
    tilemapwidget.h

    # QR Code + Serveur HTTP
    labhttpserver.cpp
    labhttpserver.h

    # Ressources
    resources.qrc
)

# --- CRÉATION DE L'EXÉCUTABLE ---
qt_add_executable(SmartResearchPublicationManagement
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# --- INCLUSIONS ET LIEN DES BIBLIOTHÈQUES ---
# Inclusion des headers OpenCV
target_include_directories(SmartResearchPublicationManagement PRIVATE ${OpenCV_INCLUDE_DIRS})

# Liaison des bibliothèques (Qt + OpenCV)
target_link_libraries(SmartResearchPublicationManagement
    PRIVATE
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts
        Qt6::Network
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::SerialPort
        Qt6::Pdf
        ${OpenCV_LIBS}
)

# --- PROPRIÉTÉS DE L'EXÉCUTABLE ---
set_target_properties(SmartResearchPublicationManagement PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# --- FINALISATION ---
qt_finalize_executable(SmartResearchPublicationManagement)
