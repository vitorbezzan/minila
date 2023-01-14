cmake_minimum_required(VERSION 3.23)
project(minila)

set(CMAKE_CXX_STANDARD 23)

# 1 - including /usr/local here for gtest suite; This may differ in your machine.
include_directories(/usr/local/include/) # << Here
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(minila SHARED include/minila/array_definition.h library.cpp)

# 2 - Creating tests executable
add_executable(run_tests tests.cpp)
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

# 3 - Add scratchpad code for quick testing/deploy
add_executable(main main.cpp)
