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
include CMakeFiles/gateway_mqtt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gateway_mqtt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gateway_mqtt.dir/flags.make

CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o: CMakeFiles/gateway_mqtt.dir/flags.make
CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o: ../gateway_mqtt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o -c /home/thomas-ubuntu/Desktop/IDOS/gateway_mqtt.cpp

CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas-ubuntu/Desktop/IDOS/gateway_mqtt.cpp > CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.i

CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas-ubuntu/Desktop/IDOS/gateway_mqtt.cpp -o CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.s

CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.requires:

.PHONY : CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.requires

CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.provides: CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.requires
	$(MAKE) -f CMakeFiles/gateway_mqtt.dir/build.make CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.provides.build
.PHONY : CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.provides

CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.provides.build: CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o


# Object files for target gateway_mqtt
gateway_mqtt_OBJECTS = \
"CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o"

# External object files for target gateway_mqtt
gateway_mqtt_EXTERNAL_OBJECTS =

gateway_mqtt: CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o
gateway_mqtt: CMakeFiles/gateway_mqtt.dir/build.make
gateway_mqtt: /usr/local/lib/libpaho-mqtt3a.so
gateway_mqtt: /usr/local/lib/libpaho-mqttpp3.so
gateway_mqtt: /usr/local/lib/libyaml-cpp.so
gateway_mqtt: CMakeFiles/gateway_mqtt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gateway_mqtt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gateway_mqtt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gateway_mqtt.dir/build: gateway_mqtt

.PHONY : CMakeFiles/gateway_mqtt.dir/build

CMakeFiles/gateway_mqtt.dir/requires: CMakeFiles/gateway_mqtt.dir/gateway_mqtt.cpp.o.requires

.PHONY : CMakeFiles/gateway_mqtt.dir/requires

CMakeFiles/gateway_mqtt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gateway_mqtt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gateway_mqtt.dir/clean

CMakeFiles/gateway_mqtt.dir/depend:
	cd /home/thomas-ubuntu/Desktop/IDOS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas-ubuntu/Desktop/IDOS /home/thomas-ubuntu/Desktop/IDOS /home/thomas-ubuntu/Desktop/IDOS/build /home/thomas-ubuntu/Desktop/IDOS/build /home/thomas-ubuntu/Desktop/IDOS/build/CMakeFiles/gateway_mqtt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gateway_mqtt.dir/depend

