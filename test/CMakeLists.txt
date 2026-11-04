project(CheckersTests  CXX;C)

# Locate GoogleTest: use an installed copy if there is one, otherwise fetch it.
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    message(STATUS "GTest not found, fetching googletest v1.14.0")
    include(FetchContent)
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
        GIT_SHALLOW    TRUE)
    # MSVC: link gtest against the same (dynamic) CRT as the rest of the project
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

if(TARGET GTest::gtest)
    set(CHECKERS_GTEST GTest::gtest)
else()
    set(CHECKERS_GTEST GTest::GTest) # FindGTest from CMake < 3.20
endif()

include(GoogleTest)

# The test program
add_executable(CheckersTests CheckersTest.cpp)
# target_link_libraries(CheckersTests PRIVATE CheckersGameLib catch sglib)
target_link_libraries(CheckersTests PRIVATE ${CHECKERS_GTEST} catch sglib CheckersGameLib)
target_compile_features(CheckersTests PRIVATE cxx_std_14) # required by googletest >= 1.13
gtest_discover_tests(CheckersTests TEST_PREFIX "CheckersGame.")

# The testApi program
add_executable(CheckersApiTest CheckersApiTest.cpp)
# target_link_libraries(CheckersApiTest PRIVATE catch sglib CheckersGameApi)
target_link_libraries(CheckersApiTest PRIVATE ${CHECKERS_GTEST} CheckersGameApi)
target_compile_features(CheckersApiTest PRIVATE cxx_std_14)
gtest_discover_tests(CheckersApiTest TEST_PREFIX "CheckersGameApi.")
