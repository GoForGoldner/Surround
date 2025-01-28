cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add test executable
add_executable(tests
  playerInfoTest.cc
  ../sources/player.cpp
  ../sources/playerInfo.cpp
  modelTest.cc
  ../sources/model.cpp
)

# Include directories
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src/headers)

# Link libraries
target_link_libraries(tests PRIVATE GTest::gtest_main sfml-graphics)

# Discover tests
include(GoogleTest)
gtest_discover_tests(tests)
