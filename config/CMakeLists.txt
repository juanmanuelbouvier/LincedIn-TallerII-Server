cmake_minimum_required (VERSION 2.6)
project (LincedInServer)

# CMake output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# The version number.
set (LincedInServer_VERSION_MAJOR 1)
set (LincedInServer_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/LincedInServerConfig.h.in"
  "${PROJECT_BINARY_DIR}/LincedInServerConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find LincedInServerConfig.h
include_directories("${PROJECT_BINARY_DIR}")

add_executable(LincedInServer ../src/main/AppInitializer.cpp)

### TESTING ###

################################
# GTest
################################
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RunUnitTests
	${PROJECT_SOURCE_DIR}/../src/test/test_main.cpp
)
target_link_libraries(RunUnitTests gtest gtest_main)

add_test(
	NAME RunUnitTests
	COMMAND RunUnitTests
)
