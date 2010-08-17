########### start prep and settings/setup section
cmake_minimum_required(VERSION 2.6) 
project(setproctitle C)

set(BUILD_VERSION "0.6")
set(PROJECT_VERSION ${BUILD_VERSION})

set(CFP "-std=c99 -Wall -pipe")

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES ppc;i386;x86_64)
    set(CMAKE_C_FLAGS_MINSIZEREL "${CFP} -Os $ENV{CFLAGS}")
    set(CMAKE_C_FLAGS_RELEASE "${CFP} -O2 $ENV{CFLAGS}")
    set(CMAKE_C_FLAGS_DEBUG "-g ${CFP} -Werror -pedantic $ENV{CFLAGS}")
else(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS 
        "-Wl,--hash-style=gnu -Wl,--as-needed -Wl,--no-undefined $ENV{LDFLAGS}")
    set(CMAKE_C_FLAGS_DEBUG "-fpic -g ${CFP} -Werror -pedantic $ENV{CFLAGS}")
    set(CMAKE_C_FLAGS_RELEASE "-fpic ${CFP} -mtune=generic -O2 $ENV{CFLAGS}")
    set(CMAKE_C_FLAGS_MINSIZEREL "-fpic ${CFP} -mtune=generic -Os $ENV{CFLAGS}")
endif(APPLE)

## set a default build type if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type: Debug Release MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

## set module include path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

## ensure out of tree build
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out tree build.")
include(CheckIncludeFiles)

########### start building section
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Lua51)
if(NOT LUA51_FOUND)
    MESSAGE(FATAL_ERROR "Lua not found. It is required to build lua module.")
endif(NOT LUA51_FOUND)

check_include_files("sys/prctl.h;linux/prctl.h" HAVE_SYS_PRCTL_H)
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${LUA_INCLUDE_DIR})
# build cronkite cli binary
add_library(setproctitle SHARED setproctitle.c)
target_link_libraries(setproctitle ${LUA_LIBRARIES})
set_target_properties(setproctitle PROPERTIES
    OUTPUT_NAME setproctitle PREFIX "" SUFFIX ".so")

