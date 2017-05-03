cmake_minimum_required(VERSION 3.7)
project(test)

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp)
set(SOURCE_FILES BinarySearchTree.cpp)
add_executable(data-structures-project ${SOURCE_FILES})