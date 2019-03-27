cmake_minimum_required(VERSION 3.7)
project(data-structures-project)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Add -O0 to remove optimizations when using gcc
#IF(CMAKE_COMPILER_IS_GNUCC)
#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
#ENDIF(CMAKE_COMPILER_IS_GNUCC)

file(GLOB common
		"common/*.c"
		"common/*.cpp")

file(GLOB basic-structures
		"basic-structures/*.c"
		"basic-structures/*.cpp")

file(GLOB graphs
		"graphs/*.c"
		"graphs/*.cpp")

set(SOURCE_FILES
		"main.cpp"
		${basic-structures}
		${graphs}
		${common})

add_executable(data-structures-project ${SOURCE_FILES})
