project(LoginWindow)

set(sources
    login-window.cpp
)

set(headers
    login-window.hpp
    login-window.ui
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} 
    PRIVATE 
        "${sources}"
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        Qt6::Widgets
        Qt6::Sql
    PRIVATE
        MainWindow
        RegistrationWindow
        DataBaseHandlers
)
