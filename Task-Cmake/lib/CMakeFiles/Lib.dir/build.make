# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake

# Include any dependencies generated for this target.
include lib/CMakeFiles/Lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/Lib.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/Lib.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/Lib.dir/flags.make

lib/CMakeFiles/Lib.dir/codegen:
.PHONY : lib/CMakeFiles/Lib.dir/codegen

lib/CMakeFiles/Lib.dir/lib.cpp.o: lib/CMakeFiles/Lib.dir/flags.make
lib/CMakeFiles/Lib.dir/lib.cpp.o: lib/lib.cpp
lib/CMakeFiles/Lib.dir/lib.cpp.o: lib/CMakeFiles/Lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/Lib.dir/lib.cpp.o"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/Lib.dir/lib.cpp.o -MF CMakeFiles/Lib.dir/lib.cpp.o.d -o CMakeFiles/Lib.dir/lib.cpp.o -c /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib/lib.cpp

lib/CMakeFiles/Lib.dir/lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lib.dir/lib.cpp.i"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib/lib.cpp > CMakeFiles/Lib.dir/lib.cpp.i

lib/CMakeFiles/Lib.dir/lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lib.dir/lib.cpp.s"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib/lib.cpp -o CMakeFiles/Lib.dir/lib.cpp.s

# Object files for target Lib
Lib_OBJECTS = \
"CMakeFiles/Lib.dir/lib.cpp.o"

# External object files for target Lib
Lib_EXTERNAL_OBJECTS =

lib/libLib.so: lib/CMakeFiles/Lib.dir/lib.cpp.o
lib/libLib.so: lib/CMakeFiles/Lib.dir/build.make
lib/libLib.so: lib/CMakeFiles/Lib.dir/compiler_depend.ts
lib/libLib.so: lib/CMakeFiles/Lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libLib.so"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/Lib.dir/build: lib/libLib.so
.PHONY : lib/CMakeFiles/Lib.dir/build

lib/CMakeFiles/Lib.dir/clean:
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib && $(CMAKE_COMMAND) -P CMakeFiles/Lib.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/Lib.dir/clean

lib/CMakeFiles/Lib.dir/depend:
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/lib/CMakeFiles/Lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib/CMakeFiles/Lib.dir/depend

