find_package(GTest)

if (GTEST_FOUND)
  add_executable(test_1 test_1.cpp)

  include_directories(${CMAKE_SOURCE_DIR})
  set(LIBS GTest::GTest GTest::Main)

  target_link_libraries(test_1 ${LIBS})
else()
  message("GTest package not found, tests will not be built. To build the unit tests, first install GTest. On Ubuntu, this can be done using 'sudo apt-get install libgtest-dev'.")
endif()

