# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/saad/Downloads/Sem-5/dip/uebung01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saad/Downloads/Sem-5/dip/uebung01

# Include any dependencies generated for this target.
include CMakeFiles/uebung01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uebung01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uebung01.dir/flags.make

CMakeFiles/uebung01.dir/src/uebung01.o: CMakeFiles/uebung01.dir/flags.make
CMakeFiles/uebung01.dir/src/uebung01.o: src/uebung01.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saad/Downloads/Sem-5/dip/uebung01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uebung01.dir/src/uebung01.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uebung01.dir/src/uebung01.o -c /home/saad/Downloads/Sem-5/dip/uebung01/src/uebung01.cpp

CMakeFiles/uebung01.dir/src/uebung01.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uebung01.dir/src/uebung01.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saad/Downloads/Sem-5/dip/uebung01/src/uebung01.cpp > CMakeFiles/uebung01.dir/src/uebung01.i

CMakeFiles/uebung01.dir/src/uebung01.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uebung01.dir/src/uebung01.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saad/Downloads/Sem-5/dip/uebung01/src/uebung01.cpp -o CMakeFiles/uebung01.dir/src/uebung01.s

# Object files for target uebung01
uebung01_OBJECTS = \
"CMakeFiles/uebung01.dir/src/uebung01.o"

# External object files for target uebung01
uebung01_EXTERNAL_OBJECTS =

uebung01: CMakeFiles/uebung01.dir/src/uebung01.o
uebung01: CMakeFiles/uebung01.dir/build.make
uebung01: CMakeFiles/uebung01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saad/Downloads/Sem-5/dip/uebung01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uebung01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uebung01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uebung01.dir/build: uebung01

.PHONY : CMakeFiles/uebung01.dir/build

CMakeFiles/uebung01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uebung01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uebung01.dir/clean

CMakeFiles/uebung01.dir/depend:
	cd /home/saad/Downloads/Sem-5/dip/uebung01 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saad/Downloads/Sem-5/dip/uebung01 /home/saad/Downloads/Sem-5/dip/uebung01 /home/saad/Downloads/Sem-5/dip/uebung01 /home/saad/Downloads/Sem-5/dip/uebung01 /home/saad/Downloads/Sem-5/dip/uebung01/CMakeFiles/uebung01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uebung01.dir/depend

