# language: CMake

# ---------------------------------     Project setup      ---------------------------------
cmake_minimum_required(VERSION 3.20)

project(Lib LANGUAGES C)

# ---------------------------------     Set C settings     ---------------------------------
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -std=c17 -O2")

# ---------------------------------       Add library       --------------------------------
file(GLOB_RECURSE SOURCE_LIST "*.c" "*.h")

add_library(Lib ${SOURCE_LIST})

set_target_properties(Lib PROPERTIES LINKER_LANGUAGE C)
target_include_directories(Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
