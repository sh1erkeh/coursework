cmake_minimum_required(VERSION 3.28)

project("coursework")

add_subdirectory(libraries)

set(SOURCE_FILES 
    src/main.cpp 
    src/colorChoosers/colorChooser1.cpp
)
set(HEADER_FILES 
    include/colorChoosers/colorChooser1.hpp
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        graph-coloring
)

include(CheckCXXCompilerFlag)

function(add_cxx_compiler_flag flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if (flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if (flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

add_cxx_compiler_flag("-Wall")
add_cxx_compiler_flag("-Wextra")
add_cxx_compiler_flag("-Wpedantic")
