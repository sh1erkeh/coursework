project(GraphColoring)

set(headers
    include/graph.hpp 
    include/degree-saturation.hpp
    include/tabu-search.hpp
)

set(sources
    src/graph.cpp
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE "${sources}")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
