# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kkm/Work/c-checkers-api-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kkm/Work/c-checkers-api-master

# Include any dependencies generated for this target.
include src/CMakeFiles/CheckersGameApi.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/CheckersGameApi.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/CheckersGameApi.dir/flags.make

src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o: src/CMakeFiles/CheckersGameApi.dir/flags.make
src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o: src/CheckersGameApi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kkm/Work/c-checkers-api-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o"
	cd /home/kkm/Work/c-checkers-api-master/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o -c /home/kkm/Work/c-checkers-api-master/src/CheckersGameApi.cpp

src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.i"
	cd /home/kkm/Work/c-checkers-api-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kkm/Work/c-checkers-api-master/src/CheckersGameApi.cpp > CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.i

src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.s"
	cd /home/kkm/Work/c-checkers-api-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kkm/Work/c-checkers-api-master/src/CheckersGameApi.cpp -o CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.s

src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.requires:

.PHONY : src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.requires

src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.provides: src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CheckersGameApi.dir/build.make src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.provides.build
.PHONY : src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.provides

src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.provides.build: src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o


src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o: src/CMakeFiles/CheckersGameApi.dir/flags.make
src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o: src/TreeBoard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kkm/Work/c-checkers-api-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o"
	cd /home/kkm/Work/c-checkers-api-master/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o -c /home/kkm/Work/c-checkers-api-master/src/TreeBoard.cpp

src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.i"
	cd /home/kkm/Work/c-checkers-api-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kkm/Work/c-checkers-api-master/src/TreeBoard.cpp > CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.i

src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.s"
	cd /home/kkm/Work/c-checkers-api-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kkm/Work/c-checkers-api-master/src/TreeBoard.cpp -o CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.s

src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.requires:

.PHONY : src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.requires

src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.provides: src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CheckersGameApi.dir/build.make src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.provides.build
.PHONY : src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.provides

src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.provides.build: src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o


# Object files for target CheckersGameApi
CheckersGameApi_OBJECTS = \
"CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o" \
"CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o"

# External object files for target CheckersGameApi
CheckersGameApi_EXTERNAL_OBJECTS =

src/libCheckersGameApi.a: src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o
src/libCheckersGameApi.a: src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o
src/libCheckersGameApi.a: src/CMakeFiles/CheckersGameApi.dir/build.make
src/libCheckersGameApi.a: src/CMakeFiles/CheckersGameApi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kkm/Work/c-checkers-api-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libCheckersGameApi.a"
	cd /home/kkm/Work/c-checkers-api-master/src && $(CMAKE_COMMAND) -P CMakeFiles/CheckersGameApi.dir/cmake_clean_target.cmake
	cd /home/kkm/Work/c-checkers-api-master/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CheckersGameApi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/CheckersGameApi.dir/build: src/libCheckersGameApi.a

.PHONY : src/CMakeFiles/CheckersGameApi.dir/build

src/CMakeFiles/CheckersGameApi.dir/requires: src/CMakeFiles/CheckersGameApi.dir/CheckersGameApi.cpp.o.requires
src/CMakeFiles/CheckersGameApi.dir/requires: src/CMakeFiles/CheckersGameApi.dir/TreeBoard.cpp.o.requires

.PHONY : src/CMakeFiles/CheckersGameApi.dir/requires

src/CMakeFiles/CheckersGameApi.dir/clean:
	cd /home/kkm/Work/c-checkers-api-master/src && $(CMAKE_COMMAND) -P CMakeFiles/CheckersGameApi.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/CheckersGameApi.dir/clean

src/CMakeFiles/CheckersGameApi.dir/depend:
	cd /home/kkm/Work/c-checkers-api-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kkm/Work/c-checkers-api-master /home/kkm/Work/c-checkers-api-master/src /home/kkm/Work/c-checkers-api-master /home/kkm/Work/c-checkers-api-master/src /home/kkm/Work/c-checkers-api-master/src/CMakeFiles/CheckersGameApi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/CheckersGameApi.dir/depend

