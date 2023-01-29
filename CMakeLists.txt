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

# Setup: including all directories necessary for libraries (this can change in your system)
include_directories(/opt/homebrew/opt/openblas/include)
include_directories(/opt/homebrew/opt/lapack/include)

# Setup: finding necessary packages
find_package(GTest REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# Library object
add_library(
        minila SHARED
        library.cpp
        include/minila/base.h
        include/minila/minila.h
        include/minila/matrix.h
        include/minila/print.h
        include/minila/matrix_multiply.h
        include/minila/vector.h
)

# Test suite executable
add_executable(run_tests tests.cpp)
target_link_libraries(run_tests ${GTEST_LIBRARIES} ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)

# Scratchpad code for inline testing
add_executable(main main.cpp)
target_link_libraries(main ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)
