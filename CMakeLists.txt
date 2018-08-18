cmake_minimum_required(VERSION 3.0.2)
project(CuttleFileUI VERSION 0.2 LANGUAGES CXX)

include(CMakeToolsHelpers OPTIONAL)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
  set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} -Wextra -O3")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif()

set(SRC_INCLUDE_DIRECTORIES "src/")

file(GLOB SRCS "src/*.cpp")
file(GLOB_RECURSE TEST_SRCS "tests/*.cpp")
file(GLOB CUTTLE_TEST_SRCS "../cuttle-test/src/*.cpp")

file(GLOB HEADERS "src/*.hpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.hpp")

add_library(cuttle-parser SHARED ${SRCS} ${HEADERS})
add_executable(cuttle-parser-tests ${CUTTLE_TEST_SRCS} ${TEST_SRCS} ${HEADERS} ${TEST_HEADERS})

target_include_directories(cuttle-parser PRIVATE ${SRC_INCLUDE_DIRECTORIES})
target_include_directories(cuttle-parser-tests
    PRIVATE
    "tests/"
    "../cuttle-test/src/"
    ${SRC_INCLUDE_DIRECTORIES})

target_link_libraries(cuttle-parser-tests cuttle-parser)
