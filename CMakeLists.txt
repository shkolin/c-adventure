cmake_minimum_required(VERSION 3.15)

project(CAdventure C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(CAdventure src/main.c src/player.c)

target_link_libraries(CAdventure raylib)
