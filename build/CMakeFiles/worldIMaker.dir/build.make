# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build

# Include any dependencies generated for this target.
include CMakeFiles/worldIMaker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/worldIMaker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/worldIMaker.dir/flags.make

CMakeFiles/worldIMaker.dir/src/main.cpp.o: CMakeFiles/worldIMaker.dir/flags.make
CMakeFiles/worldIMaker.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/worldIMaker.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/worldIMaker.dir/src/main.cpp.o -c /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/src/main.cpp

CMakeFiles/worldIMaker.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/worldIMaker.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/src/main.cpp > CMakeFiles/worldIMaker.dir/src/main.cpp.i

CMakeFiles/worldIMaker.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/worldIMaker.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/src/main.cpp -o CMakeFiles/worldIMaker.dir/src/main.cpp.s

# Object files for target worldIMaker
worldIMaker_OBJECTS = \
"CMakeFiles/worldIMaker.dir/src/main.cpp.o"

# External object files for target worldIMaker
worldIMaker_EXTERNAL_OBJECTS =

bin/worldIMaker: CMakeFiles/worldIMaker.dir/src/main.cpp.o
bin/worldIMaker: CMakeFiles/worldIMaker.dir/build.make
bin/worldIMaker: lib/libglimac.a
bin/worldIMaker: lib/libimgui.a
bin/worldIMaker: /usr/lib/x86_64-linux-gnu/libGL.so
bin/worldIMaker: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/worldIMaker: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/worldIMaker: CMakeFiles/worldIMaker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/worldIMaker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/worldIMaker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/worldIMaker.dir/build: bin/worldIMaker

.PHONY : CMakeFiles/worldIMaker.dir/build

CMakeFiles/worldIMaker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/worldIMaker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/worldIMaker.dir/clean

CMakeFiles/worldIMaker.dir/depend:
	cd /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build /home/laurine/Documents/IMAC2/WorldIMAC/imac2-worldIMaker/build/CMakeFiles/worldIMaker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/worldIMaker.dir/depend

