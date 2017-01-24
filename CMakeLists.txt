cmake_minimum_required(VERSION 3.6)
project(SPlabs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES source/wc/WordCount.cpp)
add_executable(SPlabs ${SOURCE_FILES})