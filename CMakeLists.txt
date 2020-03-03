cmake_minimum_required(VERSION 3.5)
project(DuplicateFileRemover)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp crypto/md5.cpp crypto/md5.h tinydir/tinydir.h)
add_executable(DuplicateFileRemover ${SOURCE_FILES})