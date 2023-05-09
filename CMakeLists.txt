# Please check README.md for copyright and licensing.
# If not available contact developer at vitor@bezzan.com
# Code is distributed as-is without any guarantee of purpose.

# Starting point of build
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)
project(minila)
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 0)
SET(VERSION_FEATURE 1)
SET(VERSION_PATCH 0)
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
SET(VERSION "${VERSION}.${VERSION_FEATURE}.${VERSION_PATCH}")
MESSAGE("Version: ${VERSION}")

# Setup: finding necessary packages. May differ in your environment.
include_directories(/usr/local/include/openblas)
include_directories(/usr/local/include/lapack)
include_directories(/usr/local/include/lapacke)

find_package(GTest REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# Library object
add_library(
        minila SHARED
        library.cpp
)
target_link_libraries(minila ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)

# Test suite executable
add_executable(run_tests tests.cpp)
target_link_libraries(run_tests ${GTEST_LIBRARIES} ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)

# Scratchpad code for inline testing
add_executable(main main.cpp)
target_link_libraries(main ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)
