cmake_minimum_required(VERSION 3.6)
project(crypto)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/crypto/des/des.c)
add_executable(SPlabs ${SOURCE_FILES})