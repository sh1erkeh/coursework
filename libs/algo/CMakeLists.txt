cmake_minimum_required(VERSION 3.11)

project(algo)

add_library(
    algo 
    sources/graph.cpp
    sources/dsatur.cpp
)

set_target_properties(
    algo
    PROPERTIES 
    PUBLIC_HEADER "headers/graph.h;headers/dsatur.h"
)

install(
    TARGETS algo
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)
