cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(CAdventure VERSION 0.0.1 LANGUAGES C)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

file(GLOB C "src/*.c")
add_executable(${PROJECT_NAME} ${C})

target_link_libraries(${PROJECT_NAME} raylib)
