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
CMAKE_SOURCE_DIR = /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build

# Include any dependencies generated for this target.
include module1/tests/CMakeFiles/test_module1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include module1/tests/CMakeFiles/test_module1.dir/compiler_depend.make

# Include the progress variables for this target.
include module1/tests/CMakeFiles/test_module1.dir/progress.make

# Include the compile flags for this target's objects.
include module1/tests/CMakeFiles/test_module1.dir/flags.make

module1/tests/CMakeFiles/test_module1.dir/codegen:
.PHONY : module1/tests/CMakeFiles/test_module1.dir/codegen

module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.o: module1/tests/CMakeFiles/test_module1.dir/flags.make
module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.o: /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/module1/tests/test_module1.cpp
module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.o: module1/tests/CMakeFiles/test_module1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.o"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.o -MF CMakeFiles/test_module1.dir/test_module1.cpp.o.d -o CMakeFiles/test_module1.dir/test_module1.cpp.o -c /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/module1/tests/test_module1.cpp

module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_module1.dir/test_module1.cpp.i"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/module1/tests/test_module1.cpp > CMakeFiles/test_module1.dir/test_module1.cpp.i

module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_module1.dir/test_module1.cpp.s"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/module1/tests/test_module1.cpp -o CMakeFiles/test_module1.dir/test_module1.cpp.s

# Object files for target test_module1
test_module1_OBJECTS = \
"CMakeFiles/test_module1.dir/test_module1.cpp.o"

# External object files for target test_module1
test_module1_EXTERNAL_OBJECTS =

module1/tests/test_module1: module1/tests/CMakeFiles/test_module1.dir/test_module1.cpp.o
module1/tests/test_module1: module1/tests/CMakeFiles/test_module1.dir/build.make
module1/tests/test_module1: module1/tests/CMakeFiles/test_module1.dir/compiler_depend.ts
module1/tests/test_module1: /usr/local/lib/libgtest_main.a
module1/tests/test_module1: /usr/local/lib/libgtest.a
module1/tests/test_module1: module1/tests/CMakeFiles/test_module1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_module1"
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_module1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
module1/tests/CMakeFiles/test_module1.dir/build: module1/tests/test_module1
.PHONY : module1/tests/CMakeFiles/test_module1.dir/build

module1/tests/CMakeFiles/test_module1.dir/clean:
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_module1.dir/cmake_clean.cmake
.PHONY : module1/tests/CMakeFiles/test_module1.dir/clean

module1/tests/CMakeFiles/test_module1.dir/depend:
	cd /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/module1/tests /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests /mnt/c/Code_Setup/Turing/Turing_Tasks/Task-Cmake/my_project/build/module1/tests/CMakeFiles/test_module1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : module1/tests/CMakeFiles/test_module1.dir/depend

