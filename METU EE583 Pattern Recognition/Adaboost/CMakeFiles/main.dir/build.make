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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ege/ee583_project/Adaboost

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ege/ee583_project/Adaboost

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ege/ee583_project/Adaboost/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/ege/ee583_project/Adaboost/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ege/ee583_project/Adaboost/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ege/ee583_project/Adaboost/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/main.dir/main.cpp.o.requires

CMakeFiles/main.dir/main.cpp.o.provides: CMakeFiles/main.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/main.cpp.o.provides

CMakeFiles/main.dir/main.cpp.o.provides.build: CMakeFiles/main.dir/main.cpp.o

CMakeFiles/main.dir/sorteddynamicqueue.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/sorteddynamicqueue.cpp.o: sorteddynamicqueue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ege/ee583_project/Adaboost/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/sorteddynamicqueue.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/sorteddynamicqueue.cpp.o -c /home/ege/ee583_project/Adaboost/sorteddynamicqueue.cpp

CMakeFiles/main.dir/sorteddynamicqueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/sorteddynamicqueue.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ege/ee583_project/Adaboost/sorteddynamicqueue.cpp > CMakeFiles/main.dir/sorteddynamicqueue.cpp.i

CMakeFiles/main.dir/sorteddynamicqueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/sorteddynamicqueue.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ege/ee583_project/Adaboost/sorteddynamicqueue.cpp -o CMakeFiles/main.dir/sorteddynamicqueue.cpp.s

CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.requires:
.PHONY : CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.requires

CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.provides: CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.provides

CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.provides.build: CMakeFiles/main.dir/sorteddynamicqueue.cpp.o

CMakeFiles/main.dir/enode.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/enode.cpp.o: enode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ege/ee583_project/Adaboost/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/main.dir/enode.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/main.dir/enode.cpp.o -c /home/ege/ee583_project/Adaboost/enode.cpp

CMakeFiles/main.dir/enode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/enode.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ege/ee583_project/Adaboost/enode.cpp > CMakeFiles/main.dir/enode.cpp.i

CMakeFiles/main.dir/enode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/enode.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ege/ee583_project/Adaboost/enode.cpp -o CMakeFiles/main.dir/enode.cpp.s

CMakeFiles/main.dir/enode.cpp.o.requires:
.PHONY : CMakeFiles/main.dir/enode.cpp.o.requires

CMakeFiles/main.dir/enode.cpp.o.provides: CMakeFiles/main.dir/enode.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/enode.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/enode.cpp.o.provides

CMakeFiles/main.dir/enode.cpp.o.provides.build: CMakeFiles/main.dir/enode.cpp.o

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/sorteddynamicqueue.cpp.o" \
"CMakeFiles/main.dir/enode.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/sorteddynamicqueue.cpp.o
main: CMakeFiles/main.dir/enode.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/local/lib/libopencv_videostab.so.2.4.9
main: /usr/local/lib/libopencv_video.so.2.4.9
main: /usr/local/lib/libopencv_ts.a
main: /usr/local/lib/libopencv_superres.so.2.4.9
main: /usr/local/lib/libopencv_stitching.so.2.4.9
main: /usr/local/lib/libopencv_photo.so.2.4.9
main: /usr/local/lib/libopencv_ocl.so.2.4.9
main: /usr/local/lib/libopencv_objdetect.so.2.4.9
main: /usr/local/lib/libopencv_nonfree.so.2.4.9
main: /usr/local/lib/libopencv_ml.so.2.4.9
main: /usr/local/lib/libopencv_legacy.so.2.4.9
main: /usr/local/lib/libopencv_imgproc.so.2.4.9
main: /usr/local/lib/libopencv_highgui.so.2.4.9
main: /usr/local/lib/libopencv_gpu.so.2.4.9
main: /usr/local/lib/libopencv_flann.so.2.4.9
main: /usr/local/lib/libopencv_features2d.so.2.4.9
main: /usr/local/lib/libopencv_core.so.2.4.9
main: /usr/local/lib/libopencv_contrib.so.2.4.9
main: /usr/local/lib/libopencv_calib3d.so.2.4.9
main: /usr/lib/i386-linux-gnu/libGLU.so
main: /usr/lib/i386-linux-gnu/libGL.so
main: /usr/lib/i386-linux-gnu/libSM.so
main: /usr/lib/i386-linux-gnu/libICE.so
main: /usr/lib/i386-linux-gnu/libX11.so
main: /usr/lib/i386-linux-gnu/libXext.so
main: /usr/local/lib/libopencv_nonfree.so.2.4.9
main: /usr/local/lib/libopencv_ocl.so.2.4.9
main: /usr/local/lib/libopencv_gpu.so.2.4.9
main: /usr/local/lib/libopencv_photo.so.2.4.9
main: /usr/local/lib/libopencv_objdetect.so.2.4.9
main: /usr/local/lib/libopencv_legacy.so.2.4.9
main: /usr/local/lib/libopencv_video.so.2.4.9
main: /usr/local/lib/libopencv_ml.so.2.4.9
main: /usr/local/lib/libopencv_calib3d.so.2.4.9
main: /usr/local/lib/libopencv_features2d.so.2.4.9
main: /usr/local/lib/libopencv_highgui.so.2.4.9
main: /usr/local/lib/libopencv_imgproc.so.2.4.9
main: /usr/local/lib/libopencv_flann.so.2.4.9
main: /usr/local/lib/libopencv_core.so.2.4.9
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/sorteddynamicqueue.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/enode.cpp.o.requires
.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/ege/ee583_project/Adaboost && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ege/ee583_project/Adaboost /home/ege/ee583_project/Adaboost /home/ege/ee583_project/Adaboost /home/ege/ee583_project/Adaboost /home/ege/ee583_project/Adaboost/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

