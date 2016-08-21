cmake_minimum_required (VERSION 2.6)
project (LincedInServer)

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

add_executable(LincedInServer ../src/AppInitializer.cpp)

### TESTING ###
include(CTest)

# does the application run 
add_test (RunsOK LincedInServer)

#define a macro to simplify adding tests, then use it
macro (do_test name app arg result)
  add_test (${name} ${app} ${arg})
  set_tests_properties (${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# do a bunch of result based tests
do_test ("VersionIsOK" LincedInServer "" "1.0")