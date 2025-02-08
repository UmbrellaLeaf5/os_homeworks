# language: CMake

# Set local vars from .cmake/settings.json
file(READ "${CMAKE_CURRENT_LIST_DIR}/settings.json" REPO_JSON)

string(JSON JSON_LEN LENGTH ${REPO_JSON})
math(EXPR JSON_LEN "${JSON_LEN} - 1")

foreach(INDEX RANGE ${JSON_LEN})
  string(JSON JSON_KEY MEMBER ${REPO_JSON} ${INDEX})
  string(JSON JSON_VALUE GET ${REPO_JSON} "${JSON_KEY}")

  string(REGEX REPLACE "\\[|\\]|\"| " "" JSON_VALUE "${JSON_VALUE}")
  string(REPLACE "," ";" JSON_VALUE "${JSON_VALUE}")

  set("${JSON_KEY}" "${JSON_VALUE}")
endforeach()

# Project setup
set(REPO_FOLDER ${CMAKE_CURRENT_LIST_DIR})

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES ${REPO_LANGUAGES})

find_library(${LIB_NAME} ../)

# Set language settings
if("CXX" IN_LIST REPO_LANGUAGES)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

  # less speed, more warnings = less potential errors in code (?)
  # set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -std=c++23 -O2 -Wfloat-equal -Wconversion -Wlogical-op -Wduplicated-cond")
  # source: https://codeforces.com/blog/entry/15547?locale=ru
endif()

if("C" IN_LIST REPO_LANGUAGES)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  string(REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

# Functions

# Copy non-source subproject files to binary folder.
#
# Args:
# EXCEPT_FILES_LIST_NAME: Name of list of file names to avoid copying
#
# Does:
# This function copies all files from current source directory
# (specified by CMAKE_CURRENT_SOURCE_DIR) to project's binary directory
# (specified by PROJECT_BINARY_DIR), excluding files that match source
# and header file formats (specified by SOURCES_FORMAT and HEADERS_FORMAT).
function(CopyExtraFiles EXCEPT_FILES_LIST_NAME)
  file(GLOB_RECURSE EXTRA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
  file(GLOB_RECURSE PROJECT_FILES ${SOURCES_FORMAT} ${HEADERS_FORMAT})

  list(REMOVE_ITEM EXTRA_FILES ${PROJECT_FILES} ${${EXCEPT_FILES_LIST_NAME}})

  file(COPY ${EXTRA_FILES} DESTINATION ${PROJECT_BINARY_DIR})
endfunction()

# Gets last element of list.
#
# Args:
# LIST_NAME: Name of list to get  last element from.
# LAST_ELEM_OUTPUT: name of variable to store last element in.
#
# Returns:
# Stores last element of list in output_variable.
# If list is empty, sets LAST_ELEM_OUTPUT to NOTFOUND.
function(LastElement LIST_NAME LAST_ELEM_OUTPUT)
  list(LENGTH "${LIST_NAME}" LIST_LEN)
  math(EXPR LIST_LAST "${LIST_LEN} - 1")
  list(GET "${LIST_NAME}" ${LIST_LAST} LAST_ELEM)

  set(${LAST_ELEM_OUTPUT} "${LAST_ELEM}" PARENT_SCOPE)
endfunction()
