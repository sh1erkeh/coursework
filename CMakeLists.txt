cmake_minimum_required(VERSION 3.28)

project("coursework")

add_subdirectory(lib)

set(CMAKE_EXPORT_COMPILER_COMMANDS=1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

add_executable(${PROJECT_NAME}
    src/main.cpp 
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        graph-coloring
)
