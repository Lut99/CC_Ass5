# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/lut_99/UvA/C++/Ass5/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lut_99/UvA/C++/Ass5/src/build

# Include any dependencies generated for this target.
include CMakeFiles/VirusGame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VirusGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VirusGame.dir/flags.make

CMakeFiles/VirusGame.dir/VirusGame.cpp.o: CMakeFiles/VirusGame.dir/flags.make
CMakeFiles/VirusGame.dir/VirusGame.cpp.o: ../VirusGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lut_99/UvA/C++/Ass5/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VirusGame.dir/VirusGame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VirusGame.dir/VirusGame.cpp.o -c /home/lut_99/UvA/C++/Ass5/src/VirusGame.cpp

CMakeFiles/VirusGame.dir/VirusGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VirusGame.dir/VirusGame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lut_99/UvA/C++/Ass5/src/VirusGame.cpp > CMakeFiles/VirusGame.dir/VirusGame.cpp.i

CMakeFiles/VirusGame.dir/VirusGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VirusGame.dir/VirusGame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lut_99/UvA/C++/Ass5/src/VirusGame.cpp -o CMakeFiles/VirusGame.dir/VirusGame.cpp.s

CMakeFiles/VirusGame.dir/VirusGame.cpp.o.requires:

.PHONY : CMakeFiles/VirusGame.dir/VirusGame.cpp.o.requires

CMakeFiles/VirusGame.dir/VirusGame.cpp.o.provides: CMakeFiles/VirusGame.dir/VirusGame.cpp.o.requires
	$(MAKE) -f CMakeFiles/VirusGame.dir/build.make CMakeFiles/VirusGame.dir/VirusGame.cpp.o.provides.build
.PHONY : CMakeFiles/VirusGame.dir/VirusGame.cpp.o.provides

CMakeFiles/VirusGame.dir/VirusGame.cpp.o.provides.build: CMakeFiles/VirusGame.dir/VirusGame.cpp.o


# Object files for target VirusGame
VirusGame_OBJECTS = \
"CMakeFiles/VirusGame.dir/VirusGame.cpp.o"

# External object files for target VirusGame
VirusGame_EXTERNAL_OBJECTS =

VirusGame: CMakeFiles/VirusGame.dir/VirusGame.cpp.o
VirusGame: CMakeFiles/VirusGame.dir/build.make
VirusGame: /usr/lib/x86_64-linux-gnu/libSDL2_gfx.so
VirusGame: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
VirusGame: /usr/lib/x86_64-linux-gnu/libSDL2main.a
VirusGame: /usr/lib/x86_64-linux-gnu/libSDL2.so
VirusGame: CMakeFiles/VirusGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lut_99/UvA/C++/Ass5/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VirusGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VirusGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VirusGame.dir/build: VirusGame

.PHONY : CMakeFiles/VirusGame.dir/build

CMakeFiles/VirusGame.dir/requires: CMakeFiles/VirusGame.dir/VirusGame.cpp.o.requires

.PHONY : CMakeFiles/VirusGame.dir/requires

CMakeFiles/VirusGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VirusGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VirusGame.dir/clean

CMakeFiles/VirusGame.dir/depend:
	cd /home/lut_99/UvA/C++/Ass5/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lut_99/UvA/C++/Ass5/src /home/lut_99/UvA/C++/Ass5/src /home/lut_99/UvA/C++/Ass5/src/build /home/lut_99/UvA/C++/Ass5/src/build /home/lut_99/UvA/C++/Ass5/src/build/CMakeFiles/VirusGame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VirusGame.dir/depend

