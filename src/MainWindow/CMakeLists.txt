project(MainWindow)

set(sources
    main-window.cpp
)

set(headers
    main-window.h
    main-window.ui
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE "${sources}")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC GraphColoring Utilities Qt6::Widgets Qt6::Sql)
