project(CheckersGame CXX)

#add_compile_options(-std=gnu99)
add_compile_options(-std=c++11)

# All sources that also need to be included into a static library
add_library(CheckersGameLib STATIC CheckersGame.cpp)
target_include_directories(CheckersGameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CheckersGameLib)

# All sources that also need to be included into a CheckersGameAPI
add_library(CheckersGameApi STATIC CheckersGameApi.cpp TreeBoard.cpp)
target_include_directories(CheckersGameApi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CheckersGameApi PRIVATE CheckersGameLib)