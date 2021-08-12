cmake_minimum_required(VERSION 3.5)

project( CIRQUEUE_TEST )

SET( CMAKE_BUILD_TYPE "Debug" ) 
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" )

include_directories(${PROJECT_SOURCE_DIR}/include)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )


add_executable( CIRQUEUE_TEST ${PROJECT_SOURCE_DIR}/src/Queue_test.cc )

target_link_libraries( CIRQUEUE_TEST  gtest pthread )