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
include examples/CMakeFiles/BuildGameTree.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/BuildGameTree.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/BuildGameTree.dir/flags.make

examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o: examples/CMakeFiles/BuildGameTree.dir/flags.make
examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o: examples/BuildGameTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kkm/Work/c-checkers-api-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o"
	cd /home/kkm/Work/c-checkers-api-master/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o -c /home/kkm/Work/c-checkers-api-master/examples/BuildGameTree.cpp

examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.i"
	cd /home/kkm/Work/c-checkers-api-master/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kkm/Work/c-checkers-api-master/examples/BuildGameTree.cpp > CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.i

examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.s"
	cd /home/kkm/Work/c-checkers-api-master/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kkm/Work/c-checkers-api-master/examples/BuildGameTree.cpp -o CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.s

examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.requires:

.PHONY : examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.requires

examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.provides: examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/BuildGameTree.dir/build.make examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.provides.build
.PHONY : examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.provides

examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.provides.build: examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o


# Object files for target BuildGameTree
BuildGameTree_OBJECTS = \
"CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o"

# External object files for target BuildGameTree
BuildGameTree_EXTERNAL_OBJECTS =

examples/BuildGameTree: examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o
examples/BuildGameTree: examples/CMakeFiles/BuildGameTree.dir/build.make
examples/BuildGameTree: src/libCheckersGameApi.a
examples/BuildGameTree: src/libCheckersGameLib.a
examples/BuildGameTree: examples/CMakeFiles/BuildGameTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kkm/Work/c-checkers-api-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BuildGameTree"
	cd /home/kkm/Work/c-checkers-api-master/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BuildGameTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/BuildGameTree.dir/build: examples/BuildGameTree

.PHONY : examples/CMakeFiles/BuildGameTree.dir/build

examples/CMakeFiles/BuildGameTree.dir/requires: examples/CMakeFiles/BuildGameTree.dir/BuildGameTree.cpp.o.requires

.PHONY : examples/CMakeFiles/BuildGameTree.dir/requires

examples/CMakeFiles/BuildGameTree.dir/clean:
	cd /home/kkm/Work/c-checkers-api-master/examples && $(CMAKE_COMMAND) -P CMakeFiles/BuildGameTree.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/BuildGameTree.dir/clean

examples/CMakeFiles/BuildGameTree.dir/depend:
	cd /home/kkm/Work/c-checkers-api-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kkm/Work/c-checkers-api-master /home/kkm/Work/c-checkers-api-master/examples /home/kkm/Work/c-checkers-api-master /home/kkm/Work/c-checkers-api-master/examples /home/kkm/Work/c-checkers-api-master/examples/CMakeFiles/BuildGameTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/BuildGameTree.dir/depend

