# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/june/ClionProjects/interactive_learning_object/saliency_detector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/june/ClionProjects/interactive_learning_object/saliency_detector/build

# Include any dependencies generated for this target.
include CMakeFiles/saliency_detector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/saliency_detector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/saliency_detector.dir/flags.make

CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o: CMakeFiles/saliency_detector.dir/flags.make
CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o: ../saliency_detector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/june/ClionProjects/interactive_learning_object/saliency_detector/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o -c /home/june/ClionProjects/interactive_learning_object/saliency_detector/saliency_detector.cpp

CMakeFiles/saliency_detector.dir/saliency_detector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saliency_detector.dir/saliency_detector.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/june/ClionProjects/interactive_learning_object/saliency_detector/saliency_detector.cpp > CMakeFiles/saliency_detector.dir/saliency_detector.cpp.i

CMakeFiles/saliency_detector.dir/saliency_detector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saliency_detector.dir/saliency_detector.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/june/ClionProjects/interactive_learning_object/saliency_detector/saliency_detector.cpp -o CMakeFiles/saliency_detector.dir/saliency_detector.cpp.s

CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.requires:
.PHONY : CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.requires

CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.provides: CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.requires
	$(MAKE) -f CMakeFiles/saliency_detector.dir/build.make CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.provides.build
.PHONY : CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.provides

CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.provides.build: CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o

# Object files for target saliency_detector
saliency_detector_OBJECTS = \
"CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o"

# External object files for target saliency_detector
saliency_detector_EXTERNAL_OBJECTS =

libsaliency_detector.a: CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o
libsaliency_detector.a: CMakeFiles/saliency_detector.dir/build.make
libsaliency_detector.a: CMakeFiles/saliency_detector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libsaliency_detector.a"
	$(CMAKE_COMMAND) -P CMakeFiles/saliency_detector.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/saliency_detector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/saliency_detector.dir/build: libsaliency_detector.a
.PHONY : CMakeFiles/saliency_detector.dir/build

CMakeFiles/saliency_detector.dir/requires: CMakeFiles/saliency_detector.dir/saliency_detector.cpp.o.requires
.PHONY : CMakeFiles/saliency_detector.dir/requires

CMakeFiles/saliency_detector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/saliency_detector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/saliency_detector.dir/clean

CMakeFiles/saliency_detector.dir/depend:
	cd /home/june/ClionProjects/interactive_learning_object/saliency_detector/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/june/ClionProjects/interactive_learning_object/saliency_detector /home/june/ClionProjects/interactive_learning_object/saliency_detector /home/june/ClionProjects/interactive_learning_object/saliency_detector/build /home/june/ClionProjects/interactive_learning_object/saliency_detector/build /home/june/ClionProjects/interactive_learning_object/saliency_detector/build/CMakeFiles/saliency_detector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/saliency_detector.dir/depend

