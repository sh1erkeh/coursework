cmake_minimum_required(VERSION 3.28)

project("coursework")

add_subdirectory(libraries)
set(CMAKE_PREFIX_PATH "~/Qt/6.8.1/gcc_64/lib/cmake/Qt6")

find_package(Qt6 6.8.1 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE "graph-algorithms;Qt6::Core")

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

# example usage
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-Wpedantic")
