cmake_minimum_required (VERSION 2.6)
project (LincedInServer)

# Compiler
SET (CMAKE_CXX_FLAGS "-std=c++11 -g -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

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

set (APP_SOURCE "${PROJECT_SOURCE_DIR}/../src/main")

set (SOURCES
    ${APP_SOURCE}/service/Logger/Logger.cpp
    
    ${APP_SOURCE}/service/MongooseServer/Server.cpp
    ${APP_SOURCE}/service/MongooseServer/ServerClient.cpp
    
    ${APP_SOURCE}/service/HTTP/HTTPRequestHandler.cpp
    
    ${APP_SOURCE}/service/HTTP/Message/HTTPRequest.cpp
    ${APP_SOURCE}/service/HTTP/Message/HTTPResponse.cpp
    ${APP_SOURCE}/service/HTTP/Message/HTTPMessageBuilder.cpp
    
    ${APP_SOURCE}/service/Handlers/HelloWorldJsonHandler.cpp
    ${APP_SOURCE}/service/Handlers/DefaultHandler.cpp
    ${APP_SOURCE}/service/Handlers/SharedServerHandler.cpp
    
    ${APP_SOURCE}/service/SharedServerAPI/SharedServerAPI.cpp
    
    ${APP_SOURCE}/Utils/DateUtils.cpp
    ${APP_SOURCE}/Utils/PathUtils.cpp
    ${APP_SOURCE}/Utils/StringUtils.cpp
    ${APP_SOURCE}/Utils/VectorUtils.cpp
    )
    
set (MAIN_CPP
    ${APP_SOURCE}/AppInitializer.cpp
    )

add_library(lincedinapp ${SOURCES})

add_executable(LincedInAppServer ${MAIN_CPP})

target_link_libraries (LincedInAppServer lincedinapp)

##################################
# External Libraries
##################################

find_package (Threads)

# Adding dl
if (NOT WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} dl)
endif (NOT WIN32)

# Adding sockets for Win32
if (WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} ws2_32)
endif (WIN32)

# MONGOOSE
set (MONGOOSE_SOURCES
    ${APP_SOURCE}/service/MongooseServer/mongoose/mongoose.c
    )

add_definitions(-DMG_ENABLE_THREADS)    

add_library (mongoose ${MONGOOSE_SOURCES})

target_link_libraries (mongoose ${EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# JSON CPP
set (JSON_SOURCES
    ${APP_SOURCE}/service/Json/json/jsoncpp.cpp
    )
add_library(json ${JSON_SOURCES})

target_link_libraries (LincedInAppServer mongoose json pthread)

#LevelDB is installed from apt-get install libsnappy-dev libleveldb-dev
target_link_libraries (LincedInAppServer snappy leveldb)

### TESTING ###

################################
# GTest
################################
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set (TEST_SOURCE "${PROJECT_SOURCE_DIR}/../src/test")

add_executable(RunUnitTests
	${TEST_SOURCE}/test_main.cpp
	${TEST_SOURCE}/UtilsTest.cpp
)
# Test libraries
target_link_libraries(RunUnitTests gtest gtest_main)

#Libraries from LincedInAppServer
target_link_libraries (RunUnitTests lincedinapp)

#External libraries
target_link_libraries (RunUnitTests mongoose json pthread snappy leveldb)

add_test(
	NAME RunUnitTests
	COMMAND RunUnitTests
)
