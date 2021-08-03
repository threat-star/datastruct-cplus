cmake_minimum_required(VERSION 3.5)

project( LRU_test )

SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set( SOURCES ${PROJECT_SOURCE_DIR}/src )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

add_executable( LRU_test ${SOURCES}/LRU_test.cc )

target_include_directories( LRU_test PRIVATE ${PROJECT_SOURCE_DIR}/include )