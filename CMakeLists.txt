cmake_minimum_required(VERSION 3.28)

project(timetable VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "~/Qt/6.8.1/gcc_64/")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Core Gui)

add_subdirectory(lib)
add_subdirectory(src)

add_executable(${PROJECT_NAME}
    src/main.cpp
    resources/resources.qrc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        DataBaseHandlers
        Utilities

        MainWindow
        LoginWindow
        RegistrationWindow
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Qt6::Widgets
        Qt6::Sql
        Qt6::Core
        Qt6::Gui
        GraphColoring
)
