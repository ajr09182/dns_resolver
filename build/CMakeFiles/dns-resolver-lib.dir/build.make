# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ajrathor09182/dns-resolver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ajrathor09182/dns-resolver/build

# Include any dependencies generated for this target.
include CMakeFiles/dns-resolver-lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dns-resolver-lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dns-resolver-lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dns-resolver-lib.dir/flags.make

CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o: CMakeFiles/dns-resolver-lib.dir/flags.make
CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o: /home/ajrathor09182/dns-resolver/src/DNSResolver.cpp
CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o: CMakeFiles/dns-resolver-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ajrathor09182/dns-resolver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o -MF CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o.d -o CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o -c /home/ajrathor09182/dns-resolver/src/DNSResolver.cpp

CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajrathor09182/dns-resolver/src/DNSResolver.cpp > CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.i

CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajrathor09182/dns-resolver/src/DNSResolver.cpp -o CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.s

CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o: CMakeFiles/dns-resolver-lib.dir/flags.make
CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o: /home/ajrathor09182/dns-resolver/src/DNSCache.cpp
CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o: CMakeFiles/dns-resolver-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ajrathor09182/dns-resolver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o -MF CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o.d -o CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o -c /home/ajrathor09182/dns-resolver/src/DNSCache.cpp

CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajrathor09182/dns-resolver/src/DNSCache.cpp > CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.i

CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajrathor09182/dns-resolver/src/DNSCache.cpp -o CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.s

CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o: CMakeFiles/dns-resolver-lib.dir/flags.make
CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o: /home/ajrathor09182/dns-resolver/src/DNSQuery.cpp
CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o: CMakeFiles/dns-resolver-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ajrathor09182/dns-resolver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o -MF CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o.d -o CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o -c /home/ajrathor09182/dns-resolver/src/DNSQuery.cpp

CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajrathor09182/dns-resolver/src/DNSQuery.cpp > CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.i

CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajrathor09182/dns-resolver/src/DNSQuery.cpp -o CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.s

CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o: CMakeFiles/dns-resolver-lib.dir/flags.make
CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o: /home/ajrathor09182/dns-resolver/src/ConnectionPool.cpp
CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o: CMakeFiles/dns-resolver-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ajrathor09182/dns-resolver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o -MF CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o.d -o CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o -c /home/ajrathor09182/dns-resolver/src/ConnectionPool.cpp

CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajrathor09182/dns-resolver/src/ConnectionPool.cpp > CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.i

CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajrathor09182/dns-resolver/src/ConnectionPool.cpp -o CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.s

CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o: CMakeFiles/dns-resolver-lib.dir/flags.make
CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o: /home/ajrathor09182/dns-resolver/src/Logger.cpp
CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o: CMakeFiles/dns-resolver-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ajrathor09182/dns-resolver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o -MF CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o.d -o CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o -c /home/ajrathor09182/dns-resolver/src/Logger.cpp

CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajrathor09182/dns-resolver/src/Logger.cpp > CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.i

CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajrathor09182/dns-resolver/src/Logger.cpp -o CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.s

# Object files for target dns-resolver-lib
dns__resolver__lib_OBJECTS = \
"CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o" \
"CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o" \
"CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o" \
"CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o" \
"CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o"

# External object files for target dns-resolver-lib
dns__resolver__lib_EXTERNAL_OBJECTS =

libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/src/DNSResolver.cpp.o
libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/src/DNSCache.cpp.o
libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/src/DNSQuery.cpp.o
libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/src/ConnectionPool.cpp.o
libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/src/Logger.cpp.o
libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/build.make
libdns-resolver-lib.a: CMakeFiles/dns-resolver-lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ajrathor09182/dns-resolver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libdns-resolver-lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/dns-resolver-lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dns-resolver-lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dns-resolver-lib.dir/build: libdns-resolver-lib.a
.PHONY : CMakeFiles/dns-resolver-lib.dir/build

CMakeFiles/dns-resolver-lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dns-resolver-lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dns-resolver-lib.dir/clean

CMakeFiles/dns-resolver-lib.dir/depend:
	cd /home/ajrathor09182/dns-resolver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ajrathor09182/dns-resolver /home/ajrathor09182/dns-resolver /home/ajrathor09182/dns-resolver/build /home/ajrathor09182/dns-resolver/build /home/ajrathor09182/dns-resolver/build/CMakeFiles/dns-resolver-lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/dns-resolver-lib.dir/depend

