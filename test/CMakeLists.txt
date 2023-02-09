add_executable(test_1 test_1.cpp)

include_directories(${CMAKE_SOURCE_DIR})
find_package(GTest REQUIRED)
set(LIBS GTest::GTest GTest::Main)

target_link_libraries(test_1 ${LIBS})
