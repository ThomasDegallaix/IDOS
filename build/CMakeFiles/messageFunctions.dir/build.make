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
include CMakeFiles/messageFunctions.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/messageFunctions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/messageFunctions.dir/flags.make

CMakeFiles/messageFunctions.dir/msg_manager.cpp.o: CMakeFiles/messageFunctions.dir/flags.make
CMakeFiles/messageFunctions.dir/msg_manager.cpp.o: ../msg_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/messageFunctions.dir/msg_manager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/messageFunctions.dir/msg_manager.cpp.o -c /home/thomas-ubuntu/Desktop/IDOS/msg_manager.cpp

CMakeFiles/messageFunctions.dir/msg_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/messageFunctions.dir/msg_manager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas-ubuntu/Desktop/IDOS/msg_manager.cpp > CMakeFiles/messageFunctions.dir/msg_manager.cpp.i

CMakeFiles/messageFunctions.dir/msg_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/messageFunctions.dir/msg_manager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas-ubuntu/Desktop/IDOS/msg_manager.cpp -o CMakeFiles/messageFunctions.dir/msg_manager.cpp.s

CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.requires:

.PHONY : CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.requires

CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.provides: CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.requires
	$(MAKE) -f CMakeFiles/messageFunctions.dir/build.make CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.provides.build
.PHONY : CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.provides

CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.provides.build: CMakeFiles/messageFunctions.dir/msg_manager.cpp.o


# Object files for target messageFunctions
messageFunctions_OBJECTS = \
"CMakeFiles/messageFunctions.dir/msg_manager.cpp.o"

# External object files for target messageFunctions
messageFunctions_EXTERNAL_OBJECTS =

libmessageFunctions.a: CMakeFiles/messageFunctions.dir/msg_manager.cpp.o
libmessageFunctions.a: CMakeFiles/messageFunctions.dir/build.make
libmessageFunctions.a: CMakeFiles/messageFunctions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmessageFunctions.a"
	$(CMAKE_COMMAND) -P CMakeFiles/messageFunctions.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/messageFunctions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/messageFunctions.dir/build: libmessageFunctions.a

.PHONY : CMakeFiles/messageFunctions.dir/build

CMakeFiles/messageFunctions.dir/requires: CMakeFiles/messageFunctions.dir/msg_manager.cpp.o.requires

.PHONY : CMakeFiles/messageFunctions.dir/requires

CMakeFiles/messageFunctions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/messageFunctions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/messageFunctions.dir/clean

CMakeFiles/messageFunctions.dir/depend:
	cd /home/thomas-ubuntu/Desktop/IDOS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas-ubuntu/Desktop/IDOS /home/thomas-ubuntu/Desktop/IDOS /home/thomas-ubuntu/Desktop/IDOS/build /home/thomas-ubuntu/Desktop/IDOS/build /home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles/messageFunctions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/messageFunctions.dir/depend

