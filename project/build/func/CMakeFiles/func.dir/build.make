# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build

# Include any dependencies generated for this target.
include func/CMakeFiles/func.dir/depend.make

# Include the progress variables for this target.
include func/CMakeFiles/func.dir/progress.make

# Include the compile flags for this target's objects.
include func/CMakeFiles/func.dir/flags.make

func/CMakeFiles/func.dir/all_functions.c.o: func/CMakeFiles/func.dir/flags.make
func/CMakeFiles/func.dir/all_functions.c.o: ../func/all_functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object func/CMakeFiles/func.dir/all_functions.c.o"
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/func.dir/all_functions.c.o   -c /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/func/all_functions.c

func/CMakeFiles/func.dir/all_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/func.dir/all_functions.c.i"
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/func/all_functions.c > CMakeFiles/func.dir/all_functions.c.i

func/CMakeFiles/func.dir/all_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/func.dir/all_functions.c.s"
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/func/all_functions.c -o CMakeFiles/func.dir/all_functions.c.s

# Object files for target func
func_OBJECTS = \
"CMakeFiles/func.dir/all_functions.c.o"

# External object files for target func
func_EXTERNAL_OBJECTS =

func/libfunc.a: func/CMakeFiles/func.dir/all_functions.c.o
func/libfunc.a: func/CMakeFiles/func.dir/build.make
func/libfunc.a: func/CMakeFiles/func.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libfunc.a"
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func && $(CMAKE_COMMAND) -P CMakeFiles/func.dir/cmake_clean_target.cmake
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/func.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
func/CMakeFiles/func.dir/build: func/libfunc.a

.PHONY : func/CMakeFiles/func.dir/build

func/CMakeFiles/func.dir/clean:
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func && $(CMAKE_COMMAND) -P CMakeFiles/func.dir/cmake_clean.cmake
.PHONY : func/CMakeFiles/func.dir/clean

func/CMakeFiles/func.dir/depend:
	cd /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/func /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func /home/danil/vscode/cpp_projects/Cpp_course/homeworks/hw_1/project/build/func/CMakeFiles/func.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : func/CMakeFiles/func.dir/depend

