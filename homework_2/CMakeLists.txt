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

# ---------------------------------      Add executable     --------------------------------
file(GLOB_RECURSE SUBFOLDERS LIST_DIRECTORIES true ".")

foreach(SUBDIR ${SUBFOLDERS})
  if(IS_DIRECTORY ${SUBDIR})
    get_filename_component(SUBPROJECT_NAME ${SUBDIR} NAME)
    set(SUBPROJECT_NAME "${PROJECT_NAME}_${SUBPROJECT_NAME}")

    file(GLOB_RECURSE SUBPROJECT_SOURCES "${SUBDIR}/*.h" "${SUBDIR}/*.c")

    add_executable(${SUBPROJECT_NAME} ${SUBPROJECT_SOURCES})

    find_library(Lib ../)
    target_link_libraries(${SUBPROJECT_NAME} PUBLIC Lib)
  endif()
endforeach()

# ---------------------------------     Copy extra files    --------------------------------
file(GLOB_RECURSE EXTRA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB_RECURSE PROJECT_FILES "*.c" "*.h" "*.md")

list(REMOVE_ITEM EXTRA_FILES ${PROJECT_FILES})

file(COPY ${EXTRA_FILES} DESTINATION ${PROJECT_BINARY_DIR})