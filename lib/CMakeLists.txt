# language: CMake

include(${REPO_FOLDER}/settings.cmake)

# Library
file(GLOB_RECURSE SOURCES ${SOURCES_FORMAT} ${HEADERS_FORMAT})

add_library(${LIB_NAME} ${SOURCES})

LastElement(REPO_LANGUAGES LIB_LANGUAGE)

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE ${LIB_LANGUAGE})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
