# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build

# Include any dependencies generated for this target.
include CMakeFiles/uebung12.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uebung12.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uebung12.dir/flags.make

CMakeFiles/uebung12.dir/src/uebung12.o: CMakeFiles/uebung12.dir/flags.make
CMakeFiles/uebung12.dir/src/uebung12.o: ../src/uebung12.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uebung12.dir/src/uebung12.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uebung12.dir/src/uebung12.o -c /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/src/uebung12.cpp

CMakeFiles/uebung12.dir/src/uebung12.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uebung12.dir/src/uebung12.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/src/uebung12.cpp > CMakeFiles/uebung12.dir/src/uebung12.i

CMakeFiles/uebung12.dir/src/uebung12.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uebung12.dir/src/uebung12.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/src/uebung12.cpp -o CMakeFiles/uebung12.dir/src/uebung12.s

CMakeFiles/uebung12.dir/src/uebung12.o.requires:

.PHONY : CMakeFiles/uebung12.dir/src/uebung12.o.requires

CMakeFiles/uebung12.dir/src/uebung12.o.provides: CMakeFiles/uebung12.dir/src/uebung12.o.requires
	$(MAKE) -f CMakeFiles/uebung12.dir/build.make CMakeFiles/uebung12.dir/src/uebung12.o.provides.build
.PHONY : CMakeFiles/uebung12.dir/src/uebung12.o.provides

CMakeFiles/uebung12.dir/src/uebung12.o.provides.build: CMakeFiles/uebung12.dir/src/uebung12.o


# Object files for target uebung12
uebung12_OBJECTS = \
"CMakeFiles/uebung12.dir/src/uebung12.o"

# External object files for target uebung12
uebung12_EXTERNAL_OBJECTS =

uebung12: CMakeFiles/uebung12.dir/src/uebung12.o
uebung12: CMakeFiles/uebung12.dir/build.make
uebung12: CMakeFiles/uebung12.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uebung12"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uebung12.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uebung12.dir/build: uebung12

.PHONY : CMakeFiles/uebung12.dir/build

CMakeFiles/uebung12.dir/requires: CMakeFiles/uebung12.dir/src/uebung12.o.requires

.PHONY : CMakeFiles/uebung12.dir/requires

CMakeFiles/uebung12.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uebung12.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uebung12.dir/clean

CMakeFiles/uebung12.dir/depend:
	cd /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12 /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12 /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build /upb/users/s/saadmann/profiles/unix/imt/dip/uebung12/build/CMakeFiles/uebung12.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uebung12.dir/depend
