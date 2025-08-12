# Specifies the minimum version of CMake required to build this project.
# This ensures that you're using a version of CMake that has the features we need.
cmake_minimum_required(VERSION 3.10)

# Defines the project name. This is used in various places by CMake.
project(SystemMonitor)

# Set the C++ standard to C++17. This enables modern C++ features.
# CMAKE_CXX_STANDARD is the variable, 17 is the value.
# REQUIRED means it's a mandatory requirement.
# EXTENSIONS OFF prevents the use of compiler-specific extensions.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find the ncurses library, which we will need later for the terminal UI.
# The find_package command looks for a configuration file for the library.
# We make it REQUIRED, so CMake will stop with an error if it can't find ncurses.
find_package(Curses REQUIRED)

# Add our executable target.
# The first argument is the name of the executable file that will be created (e.g., "monitor").
# The second argument is the source file that contains the main() function.
add_executable(monitor
  src/main.cpp
  src/display.cpp
        include/linuxParser.h
        src/linuxParser.cpp
)

# Tell the compiler where to look for our header files.
# This adds the "include" directory to the list of paths to search for #include <...>.
target_include_directories(monitor PUBLIC include)

# Link the ncurses library to our executable.
# Without this, we wouldn't be able to use any ncurses functions.
# ${CURSES_LIBRARIES} is a variable that CMake sets after finding the package.
target_link_libraries(monitor PUBLIC ${CURSES_LIBRARIES})
