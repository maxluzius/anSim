# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.2.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.2.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse

# Include any dependencies generated for this target.
include executables/assignment/CMakeFiles/assignment.dir/depend.make

# Include the progress variables for this target.
include executables/assignment/CMakeFiles/assignment.dir/progress.make

# Include the compile flags for this target's objects.
include executables/assignment/CMakeFiles/assignment.dir/flags.make

executables/assignment/CMakeFiles/assignment.dir/main.cpp.o: executables/assignment/CMakeFiles/assignment.dir/flags.make
executables/assignment/CMakeFiles/assignment.dir/main.cpp.o: /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src/executables/assignment/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object executables/assignment/CMakeFiles/assignment.dir/main.cpp.o"
	cd /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/assignment.dir/main.cpp.o -c /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src/executables/assignment/main.cpp

executables/assignment/CMakeFiles/assignment.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment.dir/main.cpp.i"
	cd /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src/executables/assignment/main.cpp > CMakeFiles/assignment.dir/main.cpp.i

executables/assignment/CMakeFiles/assignment.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment.dir/main.cpp.s"
	cd /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src/executables/assignment/main.cpp -o CMakeFiles/assignment.dir/main.cpp.s

executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.requires:
.PHONY : executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.requires

executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.provides: executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.requires
	$(MAKE) -f executables/assignment/CMakeFiles/assignment.dir/build.make executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.provides.build
.PHONY : executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.provides

executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.provides.build: executables/assignment/CMakeFiles/assignment.dir/main.cpp.o

# Object files for target assignment
assignment_OBJECTS = \
"CMakeFiles/assignment.dir/main.cpp.o"

# External object files for target assignment
assignment_EXTERNAL_OBJECTS =

bin/assignment: executables/assignment/CMakeFiles/assignment.dir/main.cpp.o
bin/assignment: executables/assignment/CMakeFiles/assignment.dir/build.make
bin/assignment: lib/libCVK_2.a
bin/assignment: lib/libCVK_AnSim.a
bin/assignment: /usr/local/lib/libglfw3.a
bin/assignment: /Users/max/Desktop/Dev/assignment/CVK_AnSim/dependencies_osx/assimp/lib/libassimp.a
bin/assignment: /usr/local/lib/libGLEW.a
bin/assignment: lib/libCVK_2.a
bin/assignment: lib/libCVK_AnSim.a
bin/assignment: /usr/local/lib/libglfw3.a
bin/assignment: /Users/max/Desktop/Dev/assignment/CVK_AnSim/dependencies_osx/assimp/lib/libassimp.a
bin/assignment: /usr/local/lib/libGLEW.a
bin/assignment: executables/assignment/CMakeFiles/assignment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/assignment"
	cd /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
executables/assignment/CMakeFiles/assignment.dir/build: bin/assignment
.PHONY : executables/assignment/CMakeFiles/assignment.dir/build

executables/assignment/CMakeFiles/assignment.dir/requires: executables/assignment/CMakeFiles/assignment.dir/main.cpp.o.requires
.PHONY : executables/assignment/CMakeFiles/assignment.dir/requires

executables/assignment/CMakeFiles/assignment.dir/clean:
	cd /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment && $(CMAKE_COMMAND) -P CMakeFiles/assignment.dir/cmake_clean.cmake
.PHONY : executables/assignment/CMakeFiles/assignment.dir/clean

executables/assignment/CMakeFiles/assignment.dir/depend:
	cd /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src/executables/assignment /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment/CMakeFiles/assignment.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : executables/assignment/CMakeFiles/assignment.dir/depend

