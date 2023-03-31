cmake_minimum_required(VERSION 3.16.3)

#SET(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

project(sparse)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(PUBLIC .)

find_package(TBB REQUIRED tbb)
if (TBB_FOUND)
	link_libraries(tbb)
	add_executable(main_policy main_policy.cpp)
else()
	message("Parallel build not possible. Install tbb for parallel build")
endif()

add_executable(main main.cpp)

add_subdirectory(test)


