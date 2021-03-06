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
CMAKE_SOURCE_DIR = /home/june/ClionProjects/interactive_learning_object/tracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/june/ClionProjects/interactive_learning_object/tracker/build

# Include any dependencies generated for this target.
include CMakeFiles/tracker_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tracker_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tracker_example.dir/flags.make

CMakeFiles/tracker_example.dir/tracker_example.cpp.o: CMakeFiles/tracker_example.dir/flags.make
CMakeFiles/tracker_example.dir/tracker_example.cpp.o: ../tracker_example.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/june/ClionProjects/interactive_learning_object/tracker/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tracker_example.dir/tracker_example.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tracker_example.dir/tracker_example.cpp.o -c /home/june/ClionProjects/interactive_learning_object/tracker/tracker_example.cpp

CMakeFiles/tracker_example.dir/tracker_example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tracker_example.dir/tracker_example.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/june/ClionProjects/interactive_learning_object/tracker/tracker_example.cpp > CMakeFiles/tracker_example.dir/tracker_example.cpp.i

CMakeFiles/tracker_example.dir/tracker_example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tracker_example.dir/tracker_example.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/june/ClionProjects/interactive_learning_object/tracker/tracker_example.cpp -o CMakeFiles/tracker_example.dir/tracker_example.cpp.s

CMakeFiles/tracker_example.dir/tracker_example.cpp.o.requires:
.PHONY : CMakeFiles/tracker_example.dir/tracker_example.cpp.o.requires

CMakeFiles/tracker_example.dir/tracker_example.cpp.o.provides: CMakeFiles/tracker_example.dir/tracker_example.cpp.o.requires
	$(MAKE) -f CMakeFiles/tracker_example.dir/build.make CMakeFiles/tracker_example.dir/tracker_example.cpp.o.provides.build
.PHONY : CMakeFiles/tracker_example.dir/tracker_example.cpp.o.provides

CMakeFiles/tracker_example.dir/tracker_example.cpp.o.provides.build: CMakeFiles/tracker_example.dir/tracker_example.cpp.o

# Object files for target tracker_example
tracker_example_OBJECTS = \
"CMakeFiles/tracker_example.dir/tracker_example.cpp.o"

# External object files for target tracker_example
tracker_example_EXTERNAL_OBJECTS =

tracker_example: CMakeFiles/tracker_example.dir/tracker_example.cpp.o
tracker_example: CMakeFiles/tracker_example.dir/build.make
tracker_example: libtracker.a
tracker_example: dlib_build/libdlib.a
tracker_example: /usr/local/lib/libopencv_highgui.so.2.4.9
tracker_example: /usr/local/lib/libopencv_core.so.2.4.9
tracker_example: /usr/local/lib/libopencv_imgproc.so.2.4.9
tracker_example: /usr/lib/x86_64-linux-gnu/libpthread.so
tracker_example: /usr/lib/x86_64-linux-gnu/libnsl.so
tracker_example: /usr/lib/x86_64-linux-gnu/libSM.so
tracker_example: /usr/lib/x86_64-linux-gnu/libICE.so
tracker_example: /usr/lib/x86_64-linux-gnu/libX11.so
tracker_example: /usr/lib/x86_64-linux-gnu/libXext.so
tracker_example: /usr/lib/x86_64-linux-gnu/libpng.so
tracker_example: /usr/lib/x86_64-linux-gnu/libjpeg.so
tracker_example: /usr/lib/libopenblas.so
tracker_example: /usr/lib/liblapack.so
tracker_example: /usr/local/lib/libopencv_core.so.2.4.9
tracker_example: CMakeFiles/tracker_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tracker_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tracker_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tracker_example.dir/build: tracker_example
.PHONY : CMakeFiles/tracker_example.dir/build

CMakeFiles/tracker_example.dir/requires: CMakeFiles/tracker_example.dir/tracker_example.cpp.o.requires
.PHONY : CMakeFiles/tracker_example.dir/requires

CMakeFiles/tracker_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tracker_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tracker_example.dir/clean

CMakeFiles/tracker_example.dir/depend:
	cd /home/june/ClionProjects/interactive_learning_object/tracker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/june/ClionProjects/interactive_learning_object/tracker /home/june/ClionProjects/interactive_learning_object/tracker /home/june/ClionProjects/interactive_learning_object/tracker/build /home/june/ClionProjects/interactive_learning_object/tracker/build /home/june/ClionProjects/interactive_learning_object/tracker/build/CMakeFiles/tracker_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tracker_example.dir/depend

