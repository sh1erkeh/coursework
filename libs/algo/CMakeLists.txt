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
    LIBRARY DESTINATION C:/Strawberry/c/lib
    ARCHIVE DESTINATION C:/Strawberry/c/lib
    RUNTIME DESTINATION C:/Strawberry/c/bin
    PUBLIC_HEADER DESTINATION C:/Strawberry/c/include
)