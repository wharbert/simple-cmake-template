cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
set(PROJECT_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

project(
  ${ProjectId}
  VERSION 1.0.0
  DESCRIPTION ""
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX C)

#CONFIGURE CMAKE
set(CMAKE_CXX_STANDARD 20) # Set required C++ Standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) #Require compiler support above standard
set(CMAKE_CXX_EXTENSIONS OFF) #Dissalow compiler-specific extensions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate the compile_commands.json file
set(CMAKE_SUPPRESS_REGENERATION ON) #Don't build ZERO_CHECK project that reruns cmake.
cmake_policy(SET CMP0063 NEW) # Enables the Visibility Property on all target types
cmake_policy(SET CMP0091 NEW) # Enables the MSVC_RUNTIME_LIBRARY property on targets

#BUILD OPTIONS
option(BUILD_TESTING "Build tests" FALSE)
option(BUILD_SHARED_LIBS "Build shared libraries" FALSE)
option(BUILD_WITH_MT "Build libraries as MultiThreaded DLL (Windows Only)" FALSE)

#INCLUDES
include(FetchContent)

include(${CMAKE_SOURCE_DIR}/tools/cmake/macros.cmake)
#include(${CMAKE_SOURCE_DIR}/tools/cmake/clangd.cmake)

#DEFINE EXTERNAL LIBS

find_package(raylib QUIET)
if (NOT raylib_FOUND)
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
    GIT_SHALLOW 1
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/_external/raylib
  )
endif()

find_package(flecs QUIET)
if (NOT flecs)
    FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v3.2.11
        GIT_SHALLOW 1
        SOURCE_DIR     ${CMAKE_SOURCE_DIR}/_external/flecs_static
    )
endif()

find_package(nlohmann_json QUIET)
if (NOT nlohmann_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        GIT_SHALLOW 1
        SOURCE_DIR     ${CMAKE_SOURCE_DIR}/_external/nlohmann_json
    )
endif()

find_package(spdlog QUIET)
if (NOT spdlog_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
        GIT_SHALLOW 1
        SOURCE_DIR     ${CMAKE_SOURCE_DIR}/_external/spdlog
    )
endif()

#FETCH EXTERNAL LIBS
FetchContent_MakeAvailable(raylib nlohmann_json flecs spdlog)

message("*********${raylib_SOURCE_DIR}*****************")

# DEFINE SOURCES : ./sources/*.[cpp|hpp|h] except ./sources/old/*
## Loop through subdirs to glob files and add to source_groups
SUBDIRLIST(SRC_DIRS ${PROJECT_SRC_DIR} TRUE)
list(REMOVE_ITEM SRC_DIRS "old")
list(APPEND SRC_DIRS "/")

FOREACH(DIR ${SRC_DIRS})
  #set(SRCS "")
  #set(HEADERS "")
  file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/${DIR}/*.h" "${PROJECT_SRC_DIR}/${DIR}/*.hpp")
  file(GLOB SRCS CONFIGURE_DEPENDS "${PROJECT_SRC_DIR}/${DIR}/*.cpp")
  source_group("Headers\\${DIR}" FILES ${HEADERS})
  source_group("Source\\${DIR}" FILES ${SRCS})
  list(APPEND PROJECT_SOURCES ${SRCS})
  list(APPEND PROJECT_HEADERS ${HEADERS})
ENDFOREACH()


# ADD EXECUTABLE
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SRC_DIR})
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}) #Set VS Default Project


#INCLUDE EXTERNAL LIBS
SUBDIRLIST(EXT_LIBS "${CMAKE_CURRENT_LIST_DIR}/_external/" FALSE)
FOREACH(subdir ${EXT_LIBS})
  target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/_external/${subdir}/include")
  target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/_external/${subdir}/src")
  target_link_libraries(${PROJECT_NAME} PRIVATE ${subdir})
ENDFOREACH()

# EXTERNAL LIB CONFIGS

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