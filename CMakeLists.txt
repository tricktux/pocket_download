# File:           CMakeLists.txt
# Description:     Code Description
# Author:		    Reinaldo Molina
# Email:          rmolin88 at gmail dot com
# Revision:	    0.0.0
# Created:        Tue Mar 05 2019 06:13
# Last Modified:  Tue Mar 05 2019 06:13

cmake_minimum_required(VERSION 3.11)

# Hunter
#		https://docs.hunter.sh/en/latest/quick-start/boost-components.html
# List of packages supported
#		https://docs.hunter.sh/en/latest/genindex.html#C
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/hunter/HunterGate.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/hunter/HunterVersion.cmake")

# Set ProjectName
project(pocket_download)

option(USE_CLANG "build application with clang" ON) # ON is the default

OPTION(ENABLE_ASAN "Enable ASAN" OFF)
OPTION(ENABLE_USAN "Enable USAN" OFF)
OPTION(ENABLE_TSAN "Enable TSAN" OFF)

IF(ENABLE_ASAN)
	MESSAGE(STATUS "ASAN enabled")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
ENDIF()

IF(ENABLE_USAN)
	MESSAGE(STATUS "USAN enabled")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")
ENDIF()

IF(ENABLE_TSAN)
	MESSAGE(STATUS "TSAN enabled")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=thread")
ENDIF()

if (USE_CLANG)
	SET (CMAKE_CXX_COMPILER "/usr/bin/clang++" )
	SET (CMAKE_AR           "/usr/bin/llvm-ar" )
	SET (CMAKE_LINKER       "/usr/bin/llvm-ld" )
	SET (CMAKE_NM           "/usr/bin/llvm-nm" )
	SET (CMAKE_OBJDUMP      "/usr/bin/llvm-objdump" )
	SET (CMAKE_RANLIB       "/usr/bin/llvm-ranlib" )
endif (USE_CLANG)

INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)

# Build with c++17 support
IF(COMPILER_SUPPORTS_CXX17)
	SET(CMAKE_CXX_STANDARD 17)
ELSE()
	MESSAGE(FATAL_ERROR
		"The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.")
ENDIF()

# add flags to release mode
# by default won't use release mode
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS}")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-strict-aliasing")
SET(CMAKE_CXX_FLAGS_RELEASE
	"${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wfatal-errors -Wextra -Wunused -Werror")

# always compile libnvc in debug mode
# for trace message use LIBNVC_DEBUG_ARG_LIST to enable
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -pedantic")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-strict-aliasing")
SET(CMAKE_CXX_FLAGS_DEBUG
	"${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wunused -Werror")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
		"Choose the type of build, options are: Debug Release
		RelWithDebInfo MinSizeRel."
		FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Specify output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Include custom macros to find Glog.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# find_package(RapidJSON REQUIRED)

# find_package(GLog REQUIRED)

# find_package(GTest REQUIRED)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/download/iniparser.cmake")

add_subdirectory("src")
add_subdirectory("docs")

option(ENABLE_TESTS "Build tests" OFF)
if(ENABLE_TESTS)
	enable_testing()
	add_subdirectory("tests")
endif()
