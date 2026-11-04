cmake_minimum_required(VERSION 3.14)
project(CheckersCmake VERSION 0.1.0 )

#add_compile_options(-std=gnu99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_subdirectory(thirdparty/catch)
add_subdirectory(thirdparty/sglib)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
