cmake_minimum_required(VERSION 3.16)

project(SmartResearchPublicationManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. CONFIGURATION QT (Avec Charts pour les stats) ---
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Charts Network)

# --- 2. CONFIGURATION OPENCV (Chemin Forcé) ---
# On pointe vers le dossier exact qui contient OpenCVConfig.cmake
set(OpenCV_DIR "C:/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/x64/mingw/lib")

# On demande à CMake de chercher UNIQUEMENT dans ce dossier pour éviter les conflits
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)

# Inclusion des headers pour éviter l'erreur "opencv2/opencv.hpp not found"
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
    resources.qrc
)

# --- 4. CRÉATION DE L'EXÉCUTABLE ---
qt_add_executable(SmartResearchPublicationManagement
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    mailsender.h mailsender.cpp
)

# --- 5. LIEN DES BIBLIOTHÈQUES (L'ordre est important) ---
target_link_libraries(SmartResearchPublicationManagement
    PRIVATE
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts    # Ajouté pour le taux d'absentéisme
        ${OpenCV_LIBS} # Ajouté pour le FaceID
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
