cmake_minimum_required(VERSION 3.10)
project(digilogic)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required libraries
find_package(raylib REQUIRED)
find_package(yoga REQUIRED)
find_package(doctest REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${DOCTEST_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE TEST_FILES "${CMAKE_SOURCE_DIR}/tests/*.cpp")

# Main executable
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} raylib)

# Test executable
add_executable(test ${TEST_FILES})
target_link_libraries(test doctest)
target_link_libraries(test raylib)

# Copy resource files if needed
# file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

# Optionally, enable testing
# enable_testing()

# Add tests
