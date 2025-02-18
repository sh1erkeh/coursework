project(graph-coloring)

set(public_headers
    include/graph.hpp 
    include/degree-saturation.hpp
    include/tabu-search.hpp
)

set(private_sources
    src/graph.cpp
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE "${private_sources}")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
