cmake_minimum_required(VERSION 3.16)

project(SmartResearchPublicationManagement VERSION 0.1 LANGUAGES CXX)

# --- CORRECTIF POUR LES CHEMINS LONGS (Gardé du 1er fichier) ---
# Évite les erreurs de compilation "MOC/AUTOGEN" dues aux espaces ou dossiers profonds
set(CMAKE_AUTOGEN_BUILD_DIR "C:/tmp/srpm_autogen")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. CONFIGURATION QT ---
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Charts Network)

# --- 2. CONFIGURATION OPENCV (Chemin propre du 2ème fichier) ---
# On pointe vers la racine C: pour éviter les erreurs d'utilisateur (zak/nadhem)
set(OpenCV_DIR "C:/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/x64/mingw/lib")

# Recherche stricte dans ce dossier
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)

# Inclusion des headers pour éviter "opencv2/opencv.hpp not found"
include_directories(${OpenCV_INCLUDE_DIRS})

# --- 3. LISTE DES SOURCES (Complète avec le module PROJET du 1er fichier) ---
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
    projet.h       # <--- Module PROJET restauré
    projet.cpp     # <--- Module PROJET restauré
    resources.qrc
)

# --- 4. CRÉATION DE L'EXÉCUTABLE ---
qt_add_executable(SmartResearchPublicationManagement
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    mailsender.h 
    mailsender.cpp
)

# --- 5. LIEN DES BIBLIOTHÈQUES ---
target_link_libraries(SmartResearchPublicationManagement
    PRIVATE
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts
        ${OpenCV_LIBS} # Pour le Face ID
        Qt6::Network
)

# --- 6. PROPRIÉTÉS ET FINALISATION ---
set_target_properties(SmartResearchPublicationManagement PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(Qt6_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartResearchPublicationManagement)
endif()