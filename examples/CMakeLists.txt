project(examples C)

# The main program
add_executable(BuildGameTree BuildGameTree.cpp)
target_link_libraries(BuildGameTree PRIVATE CheckersGameApi)
