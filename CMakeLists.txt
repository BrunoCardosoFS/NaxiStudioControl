cmake_minimum_required(VERSION 3.16)

project(NaxiStudioControl VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        frontend/control.cpp
        frontend/control.h
        frontend/control.ui
)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/frontend/resources/NaxiStudioControl.rc")

if(6 GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

    qt_add_executable(NaxiStudioControl
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        frontend/resources/control.qrc
        backend/authmanager.h
        backend/authmanager.cpp
    )
else()
    add_executable(NaxiStudioControl
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(NaxiStudioControl PRIVATE Qt6::Widgets Qt6::Network)
target_link_libraries(NaxiStudioControl PRIVATE Qt${QT_VERSION_MAJOR}::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.NaxiStudio.Control)
endif()
set_target_properties(NaxiStudioControl PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NaxiStudioControl
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NaxiStudioControl)
endif()
