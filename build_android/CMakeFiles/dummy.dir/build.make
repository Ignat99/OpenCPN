# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ignat99/Projects/OpenCPN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ignat99/Projects/OpenCPN/build_android

# Utility rule file for dummy.

# Include the progress variables for this target.
include CMakeFiles/dummy.dir/progress.make

CMakeFiles/dummy: libopencpn.a
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "dummy: Done."

dummy: CMakeFiles/dummy
dummy: CMakeFiles/dummy.dir/build.make
.PHONY : dummy

# Rule to build all files generated by this target.
CMakeFiles/dummy.dir/build: dummy
.PHONY : CMakeFiles/dummy.dir/build

CMakeFiles/dummy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dummy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dummy.dir/clean

CMakeFiles/dummy.dir/depend:
	cd /home/ignat99/Projects/OpenCPN/build_android && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ignat99/Projects/OpenCPN /home/ignat99/Projects/OpenCPN /home/ignat99/Projects/OpenCPN/build_android /home/ignat99/Projects/OpenCPN/build_android /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles/dummy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dummy.dir/depend
