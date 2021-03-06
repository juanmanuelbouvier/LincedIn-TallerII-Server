cmake_minimum_required (VERSION 2.6)
project (LincedInServer)

# Compiler
SET (CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -fprofile-arcs -O0 -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-O0 -fprofile-arcs -ftest-coverage")

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

set (APP_SOURCE "${PROJECT_SOURCE_DIR}/../src/main/src")
set (APP_HEADERS "${PROJECT_SOURCE_DIR}/../src/main/headers")

# Headers Files of source
include_directories("${APP_HEADERS}")

set (SOURCES
    ${APP_SOURCE}/service/Logger/Logger.cpp
    
    ${APP_SOURCE}/service/DB/DBManager.cpp
    ${APP_SOURCE}/service/DB/DB.cpp
    
    ${APP_SOURCE}/service/Server/Server.cpp
    ${APP_SOURCE}/service/Server/ServerClient.cpp
    
    ${APP_SOURCE}/service/HTTP/HTTPRequestHandler.cpp
    
    ${APP_SOURCE}/service/HTTP/Message/HTTPRequest.cpp
    ${APP_SOURCE}/service/HTTP/Message/HTTPResponse.cpp
    ${APP_SOURCE}/service/HTTP/Message/HTTPMessageBuilder.cpp
    
    ${APP_SOURCE}/service/Handlers/HelloWorldJsonHandler.cpp
    ${APP_SOURCE}/service/Handlers/DefaultHandler.cpp
    ${APP_SOURCE}/service/Handlers/SharedServerHandler.cpp
    ${APP_SOURCE}/service/Handlers/UserHandler.cpp
    ${APP_SOURCE}/service/Handlers/ChatHandler.cpp
    ${APP_SOURCE}/service/Handlers/FriendHandler.cpp
    ${APP_SOURCE}/service/Handlers/LoginHandler.cpp
    ${APP_SOURCE}/service/Handlers/ImagesHandler.cpp
    ${APP_SOURCE}/service/Handlers/RecommendationHandler.cpp
    ${APP_SOURCE}/service/Handlers/GeolocalizationHandler.cpp
    ${APP_SOURCE}/service/Handlers/SearchHandler.cpp
    
    ${APP_SOURCE}/service/ExternLogin/FacebookAPI.cpp
    
    ${APP_SOURCE}/service/Search/ElasticClient.cpp
    
    ${APP_SOURCE}/service/Indexer/UsersIndexer.cpp
    
    ${APP_SOURCE}/service/Firebase/FirebaseClient.cpp
    
    ${APP_SOURCE}/service/Access/AccessToken.cpp
    ${APP_SOURCE}/service/Access/AccessLog.cpp
    
    ${APP_SOURCE}/service/SharedServerAPI/SharedServerAPI.cpp
    
    ${APP_SOURCE}/utils/DateUtils.cpp
    ${APP_SOURCE}/utils/PathUtils.cpp
    ${APP_SOURCE}/utils/StringUtils.cpp
    ${APP_SOURCE}/utils/VectorUtils.cpp
    ${APP_SOURCE}/utils/JSONUtils.cpp
    ${APP_SOURCE}/utils/TokenUtils.cpp
    ${APP_SOURCE}/utils/ErrorMessage.cpp
    ${APP_SOURCE}/utils/ThreatUtils.cpp
    ${APP_SOURCE}/utils/GeoUtils.cpp
    
    ${APP_SOURCE}/settings/SettingManager.cpp
    
    ${APP_SOURCE}/model/Chat.cpp
    ${APP_SOURCE}/model/Education.cpp
    ${APP_SOURCE}/model/JobPosition.cpp
    ${APP_SOURCE}/model/Job.cpp
    ${APP_SOURCE}/model/Recommendation.cpp
    ${APP_SOURCE}/model/Skill.cpp
    ${APP_SOURCE}/model/User.cpp
    ${APP_SOURCE}/model/Image.cpp
    ${APP_SOURCE}/model/Friends.cpp
    ${APP_SOURCE}/model/Geolocalization.cpp
    ${APP_SOURCE}/model/UserActivity.cpp
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
    ${APP_SOURCE}/extern/mongoose.c
    )

add_definitions(-DMG_ENABLE_THREADS)    
add_definitions(-DMG_ENABLE_SSL)

add_library (mongoose ${MONGOOSE_SOURCES})

target_link_libraries (mongoose ${EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# JSON CPP
set (JSON_SOURCES
    ${APP_SOURCE}/extern/jsoncpp.cpp
    )
add_library(json ${JSON_SOURCES})

target_link_libraries (lincedinapp mongoose pthread json)

#LevelDB is installed from apt-get install libsnappy-dev libleveldb-dev
target_link_libraries (lincedinapp snappy leveldb)


# JWT for C ( require sudo apt-get install libjansson-dev)
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/extern_libraries/jwt)
include_directories(${PROJECT_SOURCE_DIR}/extern_libraries/jwt/include)
target_link_libraries (lincedinapp jwt_static)
target_link_libraries (lincedinapp jwt)

### TESTING ###

################################
# GTest
################################
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/extern_libraries/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set (TEST_SOURCE "${PROJECT_SOURCE_DIR}/../src/test/src")
set (TEST_HEADERS "${PROJECT_SOURCE_DIR}/../src/test/headers")

include_directories(${TEST_HEADERS})

add_executable(RunUnitTests
	${TEST_SOURCE}/mainTests.cpp
	${TEST_SOURCE}/TestHelper.cpp
	
	${TEST_SOURCE}/UtilsTest.cpp
	${TEST_SOURCE}/SettingManagerTest.cpp
	${TEST_SOURCE}/DBTest.cpp
	${TEST_SOURCE}/AccessTokenTest.cpp
	
	${TEST_SOURCE}/modeltest/EducationTest.cpp
	${TEST_SOURCE}/modeltest/RecommendationTest.cpp
	${TEST_SOURCE}/modeltest/JobPositionTest.cpp
	${TEST_SOURCE}/modeltest/JobTest.cpp
	${TEST_SOURCE}/modeltest/SkillTest.cpp
	${TEST_SOURCE}/modeltest/UserTest.cpp
	${TEST_SOURCE}/modeltest/ChatTest.cpp
	${TEST_SOURCE}/modeltest/ImageTest.cpp
	${TEST_SOURCE}/modeltest/GeolocalizationTests.cpp
	${TEST_SOURCE}/modeltest/UserActivityTest.cpp

)
# Test libraries
target_link_libraries(RunUnitTests gtest gtest_main)

#Libraries from LincedInAppServer
target_link_libraries (RunUnitTests lincedinapp)

#External libraries
#target_link_libraries (RunUnitTests mongoose json pthread snappy leveldb jwt_static)

add_test(
	NAME RunUnitTests
	COMMAND RunUnitTests
)


### GCOV with LCOV ###
## sudo apt-get install lcov 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules/")
set(CMAKE_BUILD_TYPE "Debug")

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage(run_coverage RunUnitTests coverage)
    #setup_target_for_coverage(run_coverage_server LincedInAppServer coverage)
    #target_link_libraries(lincedinapp gcov)
endif()


### DEB INSTALATION ###
## /opt/LincedInAppServer
SET(CPACK_GENERATOR "DEB")
SET(DESTINATION_DIR "/usr/share/bin/LincedInAppServer")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Bill Gates") 
#libsnappy-dev libleveldb-dev lcov libjansson-dev openssl libssl-dev
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libleveldb-dev, libsnappy-dev, libjansson-dev, libssl-dev, pkg-config, lcov")

INSTALL(TARGETS LincedInAppServer DESTINATION "${DESTINATION_DIR}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/../db" DESTINATION "${DESTINATION_DIR}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/../settings" DESTINATION "${DESTINATION_DIR}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/../logs" DESTINATION "${DESTINATION_DIR}")

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)             


INCLUDE(CPack)
