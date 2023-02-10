cmake_minimum_required(VERSION 3.16.3)

project(sparse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(PUBLIC .)

add_executable(main main.cpp)
add_subdirectory(test)
