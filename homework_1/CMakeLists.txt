# language: CMake

include(${REPO_FOLDER}/settings.cmake)

# Libraries

# find_package()
# add_library()

# Add executable
file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true ".")

string(REPLACE ";" "|" PREFIX "${TASK_PREFIXES}")

foreach(SUBDIR ${SUBDIRS})
  if(IS_DIRECTORY ${SUBDIR})
    if("${SUBDIR}" MATCHES "${PROJECT_NAME}/(${PREFIX})[^/]*$")
      get_filename_component(SUBPROJECT_NAME ${SUBDIR} NAME)
      set(SUBPROJECT_NAME "${PROJECT_NAME}_${SUBPROJECT_NAME}")

      # (files only in one subfolder)
      file(GLOB SUBPROJECT_SOURCES
        ${SUBDIR}/${HEADERS_FORMAT}
        ${SUBDIR}/${SOURCES_FORMAT}
      )

      set(SUBPROJECT_SOURCES)

      foreach(ITEM_HEADER IN LISTS HEADERS_FORMAT)
        file(GLOB ITEM_HEADER_FORMAT_SOURCES ${SUBDIR}/${ITEM_HEADER})
        list(APPEND SUBPROJECT_SOURCES ${ITEM_HEADER_FORMAT_SOURCES})
      endforeach()

      foreach(ITEM_SOURCE IN LISTS SOURCES_FORMAT)
        file(GLOB ITEM_SOURCE_FORMAT_SOURCES ${SUBDIR}/${ITEM_SOURCE})
        list(APPEND SUBPROJECT_SOURCES ${ITEM_SOURCE_FORMAT_SOURCES})
      endforeach()

      add_executable(${SUBPROJECT_NAME} ${SUBPROJECT_SOURCES})

      target_link_libraries(${SUBPROJECT_NAME} PRIVATE ${LIB_NAME})
      target_include_directories(${SUBPROJECT_NAME} PRIVATE ${REPO_FOLDER}/${LIB_NAME})
    endif()
  endif()
endforeach()

# For this project
CopyExtraFiles({})
