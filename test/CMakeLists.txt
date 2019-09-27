project(CheckersTests  CXX;C)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# The test program
add_executable(CheckersTests CheckersTest.cpp)
# target_link_libraries(CheckersTests PRIVATE CheckersGameLib catch sglib)
target_link_libraries(CheckersTests PRIVATE ${GTEST_LIBRARIES} pthread catch sglib CheckersGameLib)
# target_link_libraries(CheckersTests PRIVATE ${GTEST_LIBRARIES} pthread CheckersGameLib)

# The testApi program
add_executable(CheckersApiTest CheckersApiTest.cpp)
# target_link_libraries(CheckersApiTest PRIVATE catch sglib CheckersGameApi)
# target_link_libraries(CheckersApiTest PRIVATE ${GTEST_LIBRARIES} pthread catch sglib CheckersGameApi)
target_link_libraries(CheckersApiTest PRIVATE ${GTEST_LIBRARIES} pthread CheckersGameApi)