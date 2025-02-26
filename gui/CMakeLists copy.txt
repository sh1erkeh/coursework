cmake_minimum_required(VERSION 3.16)

project(timetable VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake/Qt6")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Убираем конфликтующие find_package
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

# Создание цели для Qt 6
qt_add_executable(timetable
    MANUAL_FINALIZATION
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    timetable_ru_RU.ts
    resources.qrc
    ../Documents/учебка/databases/data.db

)


# Подключаем библиотеки Qt
target_link_libraries(timetable PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql)

# Устанавливаем параметры для macOS
set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.timetable)

set_target_properties(timetable PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS timetable
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(timetable)
