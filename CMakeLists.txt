cmake_minimum_required(VERSION 3.16.3)

project(sparse)

include_directories(PUBLIC .)

add_executable(run test.cpp)

add_subdirectory(test)
