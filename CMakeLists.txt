cmake_minimum_required(VERSION 3.14)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(
  ${ProjectId}
  VERSION 1.0.0
  DESCRIPTION ""
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20) # Set required C++ Standard
set(CMAKE_CXX_STANDARD_REQUIRED TRUE) 
set(PROJECT_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/sources")


#Output list of dirs (result) from parent dir (curdir)
MACRO(SUBDIRLIST result curdir) 
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

#DEFINE EXTERNAL LIBS
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        GIT_SHALLOW 1
        GIT_PROGRESS   True
        SOURCE_DIR     ${CMAKE_SOURCE_DIR}/_external/raylib
    )
endif()

#FETCH EXTERNAL LIBS
FetchContent_MakeAvailable(raylib)

# DEFINE SOURCES : ./sources/*.[cpp|hpp|h] except ./sources/old/*
file(GLOB SRCS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/*.cpp")
file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/*.h")
file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/*.hpp")
source_group("Header Files" FILES  ${HEADERS})
source_group("Source Files" FILES  ${SRCS})
list(APPEND PROJECT_SOURCES ${SRCS})
list(APPEND PROJECT_SOURCES ${HEADERS})

#Loop through subdirs to glob files and add to source_groups
SUBDIRLIST(SRC_DIRS ${PROJECT_SRC_DIR})
list(REMOVE_ITEM SRC_DIRS "old")
FOREACH(DIR ${SRC_DIRS})
  set(SRCS "")
  set(HEADERS "")
  file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/${DIR}/*.cpp")
  file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/${DIR}/*.h")
  file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/${DIR}/*.hpp")
  source_group("Header Files\\${DIR}" FILES  ${HEADERS})
  source_group("Source Files\\${DIR}" FILES  ${SRCS})
  list(APPEND PROJECT_SOURCES ${SRCS})
  list(APPEND PROJECT_SOURCES ${HEADERS})
ENDFOREACH()

# ADD EXECUTABLE
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SRC_DIR})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}) #Set VS Default Project

#INCLUDE EXTERNAL LIBS
SUBDIRLIST(EXT_LIBS "${CMAKE_CURRENT_LIST_DIR}/_external/")
FOREACH(subdir ${EXT_LIBS})
  target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/_external/${subdir}/include")
  target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/_external//${subdir}/src")
  target_link_libraries(${PROJECT_NAME} PRIVATE ${subdir})
ENDFOREACH()

# Web Configurations (Raylib)
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()

#SET MACROS
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable