# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/thomas-ubuntu/Desktop/IDOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas-ubuntu/Desktop/IDOS/build

# Include any dependencies generated for this target.
include CMakeFiles/idos_message.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/idos_message.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/idos_message.dir/flags.make

CMakeFiles/idos_message.dir/idos_message.cpp.o: CMakeFiles/idos_message.dir/flags.make
CMakeFiles/idos_message.dir/idos_message.cpp.o: ../idos_message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/idos_message.dir/idos_message.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/idos_message.dir/idos_message.cpp.o -c /home/thomas-ubuntu/Desktop/IDOS/idos_message.cpp

CMakeFiles/idos_message.dir/idos_message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/idos_message.dir/idos_message.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas-ubuntu/Desktop/IDOS/idos_message.cpp > CMakeFiles/idos_message.dir/idos_message.cpp.i

CMakeFiles/idos_message.dir/idos_message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/idos_message.dir/idos_message.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas-ubuntu/Desktop/IDOS/idos_message.cpp -o CMakeFiles/idos_message.dir/idos_message.cpp.s

CMakeFiles/idos_message.dir/idos_message.cpp.o.requires:

.PHONY : CMakeFiles/idos_message.dir/idos_message.cpp.o.requires

CMakeFiles/idos_message.dir/idos_message.cpp.o.provides: CMakeFiles/idos_message.dir/idos_message.cpp.o.requires
	$(MAKE) -f CMakeFiles/idos_message.dir/build.make CMakeFiles/idos_message.dir/idos_message.cpp.o.provides.build
.PHONY : CMakeFiles/idos_message.dir/idos_message.cpp.o.provides

CMakeFiles/idos_message.dir/idos_message.cpp.o.provides.build: CMakeFiles/idos_message.dir/idos_message.cpp.o


# Object files for target idos_message
idos_message_OBJECTS = \
"CMakeFiles/idos_message.dir/idos_message.cpp.o"

# External object files for target idos_message
idos_message_EXTERNAL_OBJECTS =

idos_message: CMakeFiles/idos_message.dir/idos_message.cpp.o
idos_message: CMakeFiles/idos_message.dir/build.make
idos_message: /usr/local/lib/libyaml-cpp.so
idos_message: CMakeFiles/idos_message.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable idos_message"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/idos_message.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/idos_message.dir/build: idos_message

.PHONY : CMakeFiles/idos_message.dir/build

CMakeFiles/idos_message.dir/requires: CMakeFiles/idos_message.dir/idos_message.cpp.o.requires

.PHONY : CMakeFiles/idos_message.dir/requires

CMakeFiles/idos_message.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/idos_message.dir/cmake_clean.cmake
.PHONY : CMakeFiles/idos_message.dir/clean

CMakeFiles/idos_message.dir/depend:
	cd /home/thomas-ubuntu/Desktop/IDOS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas-ubuntu/Desktop/IDOS /home/thomas-ubuntu/Desktop/IDOS /home/thomas-ubuntu/Desktop/IDOS/build /home/thomas-ubuntu/Desktop/IDOS/build /home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles/idos_message.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/idos_message.dir/depend
