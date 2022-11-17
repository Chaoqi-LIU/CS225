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
CMAKE_SOURCE_DIR = /workspaces/cs225env/release-f22/lab/lab_avl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/cs225env/release-f22/lab/lab_avl/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/cs225.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/cs225.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/cs225.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/cs225.dir/flags.make

lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o: lib/CMakeFiles/cs225.dir/flags.make
lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o: ../lib/cs225/HSLAPixel.cpp
lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o: lib/CMakeFiles/cs225.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225env/release-f22/lab/lab_avl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o -MF CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o.d -o CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o -c /workspaces/cs225env/release-f22/lab/lab_avl/lib/cs225/HSLAPixel.cpp

lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.i"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225env/release-f22/lab/lab_avl/lib/cs225/HSLAPixel.cpp > CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.i

lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.s"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225env/release-f22/lab/lab_avl/lib/cs225/HSLAPixel.cpp -o CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.s

lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o: lib/CMakeFiles/cs225.dir/flags.make
lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o: ../lib/cs225/PNG.cpp
lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o: lib/CMakeFiles/cs225.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225env/release-f22/lab/lab_avl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o -MF CMakeFiles/cs225.dir/cs225/PNG.cpp.o.d -o CMakeFiles/cs225.dir/cs225/PNG.cpp.o -c /workspaces/cs225env/release-f22/lab/lab_avl/lib/cs225/PNG.cpp

lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs225.dir/cs225/PNG.cpp.i"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225env/release-f22/lab/lab_avl/lib/cs225/PNG.cpp > CMakeFiles/cs225.dir/cs225/PNG.cpp.i

lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs225.dir/cs225/PNG.cpp.s"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225env/release-f22/lab/lab_avl/lib/cs225/PNG.cpp -o CMakeFiles/cs225.dir/cs225/PNG.cpp.s

# Object files for target cs225
cs225_OBJECTS = \
"CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o" \
"CMakeFiles/cs225.dir/cs225/PNG.cpp.o"

# External object files for target cs225
cs225_EXTERNAL_OBJECTS =

lib/libcs225.a: lib/CMakeFiles/cs225.dir/cs225/HSLAPixel.cpp.o
lib/libcs225.a: lib/CMakeFiles/cs225.dir/cs225/PNG.cpp.o
lib/libcs225.a: lib/CMakeFiles/cs225.dir/build.make
lib/libcs225.a: lib/CMakeFiles/cs225.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/cs225env/release-f22/lab/lab_avl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcs225.a"
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/cs225.dir/cmake_clean_target.cmake
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cs225.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/cs225.dir/build: lib/libcs225.a
.PHONY : lib/CMakeFiles/cs225.dir/build

lib/CMakeFiles/cs225.dir/clean:
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/cs225.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/cs225.dir/clean

lib/CMakeFiles/cs225.dir/depend:
	cd /workspaces/cs225env/release-f22/lab/lab_avl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/cs225env/release-f22/lab/lab_avl /workspaces/cs225env/release-f22/lab/lab_avl/lib /workspaces/cs225env/release-f22/lab/lab_avl/build /workspaces/cs225env/release-f22/lab/lab_avl/build/lib /workspaces/cs225env/release-f22/lab/lab_avl/build/lib/CMakeFiles/cs225.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/cs225.dir/depend
