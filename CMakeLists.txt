cmake_minimum_required(VERSION 3.28)

project("coursework")

add_subdirectory(libraries)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE graph-algorithms)
