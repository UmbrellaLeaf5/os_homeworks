# language: CMake

# ---------------------------------     Project setup      ---------------------------------
cmake_minimum_required(VERSION 3.20)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES C)

# ---------------------------------     Set C settings     ---------------------------------
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -std=c17 -O2")

# ---------------------------------   Set CMake settings   ---------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT LINUX)
  message(WARNING "Use Linux operating system!")
endif()

# ---------------------------------    Add subdirectories   --------------------------------
file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true ".")

foreach(DIR ${SUBDIRS})
  IF(IS_DIRECTORY ${DIR})
    IF(${DIR} MATCHES "${PROJECT_NAME}/homework_[^/]*$")
      # message(${DIR})
      add_subdirectory(${DIR})
    ENDIF()
  ELSE()
    CONTINUE()
  ENDIF()
endforeach()

# Lib
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)