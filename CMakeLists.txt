cmake_minimum_required(VERSION 3.7)
project(data-structures-project)

set(CMAKE_CXX_STANDARD 11)

# Add -O0 to remove optimizations when using gcc
#IF(CMAKE_COMPILER_IS_GNUCC)
#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
#ENDIF(CMAKE_COMPILER_IS_GNUCC)

set(SOURCE_FILES main.cpp)
#set(SOURCE_FILES BinarySearchTree.cpp)
add_executable(data-structures-project ${SOURCE_FILES})