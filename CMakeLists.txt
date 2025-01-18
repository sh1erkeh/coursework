cmake_minimum_required(VERSION 3.28)

project("coursework")

# add_subdirectory(libraries)
set(CMAKE_PREFIX_PATH "~/Qt/6.8.1/gcc_64/")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/mydialogue.cpp
    src/test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Widgets
)

include(CheckCXXCompilerFlag)

function(add_cxx_compiler_flag flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if (flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if (flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif ()
        unset(flag_supported CACHE)
    endif ()
endfunction ()

# example usage
add_cxx_compiler_flag("-Wall")
add_cxx_compiler_flag("-Wextra")
add_cxx_compiler_flag("-Wpedantic")
