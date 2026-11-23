cmake_minimum_required(VERSION 3.14)
project(CheckersCmake VERSION 0.1.0 )

#add_compile_options(-std=gnu99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

# Warnings for the project's own targets (not for the fetched googletest).
function(checkers_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /utf-8)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra)
    endif()
endfunction()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
