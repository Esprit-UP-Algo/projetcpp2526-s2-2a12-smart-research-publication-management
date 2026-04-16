cmake_minimum_required(VERSION 3.16)

project(SmartResearchPublicationManagement VERSION 0.1 LANGUAGES CXX)

# --- CORRECTIF POUR LES CHEMINS LONGS ---
set(CMAKE_AUTOGEN_BUILD_DIR "C:/tmp/srpm_autogen")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. CONFIGURATION QT (AJOUT MULTIMEDIA ICI) ---
# On a ajouté Multimedia et MultimediaWidgets
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Charts Network Multimedia MultimediaWidgets SerialPort)

# --- 2. CONFIGURATION OPENCV ---
set(OpenCV_DIR "C:/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/x64/mingw/lib")
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_INCLUDE_DIRS})

# --- 3. LISTE DES SOURCES ---
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logindialog.cpp
    logindialog.h
    logindialog.ui
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
    session.h
    faceauth.cpp
    faceauth.h
    currencyconverter.h
    currencyconverter.cpp
    ocrscanner.h
    ocrscanner.cpp
    projet.h
    projet.cpp
    resources.qrc
    arduino.h
    arduino.cpp
    rfidhandler.h
    rfidhandler.cpp
    mapdialog.h
    mapdialog.cpp
    tilemapwidget.h
    tilemapwidget.cpp
)

# --- 4. CRÉATION DE L'EXÉCUTABLE ---
qt_add_executable(SmartResearchPublicationManagement
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    mailsender.h
    mailsender.cpp
)

# --- 5. LIEN DES BIBLIOTHÈQUES (AJOUT MULTIMEDIA ICI AUSSI) ---
target_link_libraries(SmartResearchPublicationManagement
    PRIVATE
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts
        Qt6::Network
        Qt6::Multimedia         # <--- AJOUTÉ
        Qt6::MultimediaWidgets  # <--- AJOUTÉ
        Qt6::SerialPort         # <--- AJOUTÉ pour Arduino RFID
        ${OpenCV_LIBS}
)

# --- 6. PROPRIÉTÉS ET FINALISATION ---
set_target_properties(SmartResearchPublicationManagement PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(Qt6_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartResearchPublicationManagement)
endif()
