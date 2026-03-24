cmake_minimum_required(VERSION 3.16)

project(SmartResearchPublicationManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. RECHERCHE DES PACKAGES (Qt + OpenCV) ---
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
find_package(OpenCV REQUIRED)

# Inclusion des headers OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# --- 2. LISTE UNIQUE DES SOURCES ---
# On regroupe tout ici pour éviter les erreurs de fichiers manquants
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
    faceauth.cpp    # Assure-toi que ce fichier existe sur ton disque
    faceauth.h      # Assure-toi que ce fichier existe sur ton disque
    resources.qrc
)

# --- 3. CRÉATION DE L'EXÉCUTABLE ---
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartResearchPublicationManagement
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(SmartResearchPublicationManagement ${PROJECT_SOURCES})
endif()

# --- 4. LIEN DES BIBLIOTHÈQUES (Qt + OpenCV) ---
target_link_libraries(SmartResearchPublicationManagement
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        ${OpenCV_LIBS}
)

# --- 5. PROPRIÉTÉS ET INSTALLATION ---
set_target_properties(SmartResearchPublicationManagement PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SmartResearchPublicationManagement
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartResearchPublicationManagement)
endif()
