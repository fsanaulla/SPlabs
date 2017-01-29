cmake_minimum_required(VERSION 3.6)
project(SPlabs)

set(CMAKE_CXX_STANDARD 11)

include_directories(resources/headers/windows.h)

set(SOURCE_FILES source/wc/WordCount.c)
add_executable(SPlabs ${SOURCE_FILES})