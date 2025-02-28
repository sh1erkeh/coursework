project(Utilities)

set(sources
    dsatur-util.cpp
    tabuSearch-util.cpp
    data-fetcher.cpp
    results-printer.cpp
)

set(headers
    dsatur-util.cpp
    tabuSearch-util.cpp
    data-fetcher.cpp
    results-printer.h
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE "${sources}")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Widgets Qt6::Sql GraphColoring)
