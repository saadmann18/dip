# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saad/dip/uebung04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saad/dip/uebung04/build

# Include any dependencies generated for this target.
include CMakeFiles/uebung04.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/uebung04.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/uebung04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uebung04.dir/flags.make

CMakeFiles/uebung04.dir/src/uebung04.cpp.o: CMakeFiles/uebung04.dir/flags.make
CMakeFiles/uebung04.dir/src/uebung04.cpp.o: ../src/uebung04.cpp
CMakeFiles/uebung04.dir/src/uebung04.cpp.o: CMakeFiles/uebung04.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saad/dip/uebung04/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uebung04.dir/src/uebung04.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/uebung04.dir/src/uebung04.cpp.o -MF CMakeFiles/uebung04.dir/src/uebung04.cpp.o.d -o CMakeFiles/uebung04.dir/src/uebung04.cpp.o -c /home/saad/dip/uebung04/src/uebung04.cpp

CMakeFiles/uebung04.dir/src/uebung04.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uebung04.dir/src/uebung04.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saad/dip/uebung04/src/uebung04.cpp > CMakeFiles/uebung04.dir/src/uebung04.cpp.i

CMakeFiles/uebung04.dir/src/uebung04.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uebung04.dir/src/uebung04.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saad/dip/uebung04/src/uebung04.cpp -o CMakeFiles/uebung04.dir/src/uebung04.cpp.s

# Object files for target uebung04
uebung04_OBJECTS = \
"CMakeFiles/uebung04.dir/src/uebung04.cpp.o"

# External object files for target uebung04
uebung04_EXTERNAL_OBJECTS =

uebung04: CMakeFiles/uebung04.dir/src/uebung04.cpp.o
uebung04: CMakeFiles/uebung04.dir/build.make
uebung04: CMakeFiles/uebung04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saad/dip/uebung04/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uebung04"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uebung04.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uebung04.dir/build: uebung04
.PHONY : CMakeFiles/uebung04.dir/build

CMakeFiles/uebung04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uebung04.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uebung04.dir/clean

CMakeFiles/uebung04.dir/depend:
	cd /home/saad/dip/uebung04/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saad/dip/uebung04 /home/saad/dip/uebung04 /home/saad/dip/uebung04/build /home/saad/dip/uebung04/build /home/saad/dip/uebung04/build/CMakeFiles/uebung04.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uebung04.dir/depend
