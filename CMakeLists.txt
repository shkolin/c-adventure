cmake_minimum_required(VERSION 3.15)

# Set the compiler to Homebrew's clang before the project() call
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(CAdventure C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Debug build settings
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

# Find raylib
find_package(raylib QUIET)

if (NOT raylib_FOUND)
    # If find_package doesn't work, try pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED raylib)

    include_directories(${RAYLIB_INCLUDE_DIRS})
    link_directories(${RAYLIB_LIBRARY_DIRS})
endif()

# Create executable
add_executable(CAdventure src/main.c)

# Link raylib
target_link_libraries(CAdventure raylib)
