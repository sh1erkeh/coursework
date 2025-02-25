cmake_minimum_required(VERSION 3.28)

project(timetable VERSION 0.1 LANGUAGES CXX)

add_subdirectory(lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

set(CMAKE_PREFIX_PATH "~/Qt/6.8.1/gcc_64/")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp

    src/dsatur-util.cpp
    src/tabu-search-util.cpp
    src/data-fetcher.cpp
    src/users-db-handler.cpp

    include/dsatur-util.hpp
    include/tabu-search-util.hpp
    include/data-fetcher.hpp
    include/users-db-handler.hpp

    ui/mainwindow.h
    ui/log-window.hpp
    ui/reg-window.hpp
    ui/mainwindow.ui
    ${TS_FILES}
)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ui/resources.qrc
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${Qt6_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Qt6::Widgets
        Qt6::Sql
        graph-coloring
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(${PROJECT_NAME})
