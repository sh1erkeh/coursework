cmake_minimum_required(VERSION 3.28)

project(graph-coloring)

add_library(${PROJECT_NAME} STATIC)

set(
    public_headers
        include/graph.hpp 
        include/degreeSaturation.hpp
)

set(
    private_sources
        src/graph.cpp
)

target_sources(${PROJECT_NAME} PRIVATE "${private_sources}")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
