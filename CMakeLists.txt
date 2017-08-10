cmake_minimum_required(VERSION 3.0.2)

include(CMakeToolsHelpers OPTIONAL)

file(GLOB SRCS "src/*.cpp")
file(GLOB TEST_SRCS "tests/*.cpp")

file(GLOB HEADERS "src/*.hpp")
file(GLOB TEST_HEADERS "tests/*.hpp")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++17")

if(UNIX)
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
  set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} -Wextra")
endif(UNIX)

add_library(husky SHARED ${SRCS} ${HEADERS})
add_executable(tests ${TEST_SRCS} ${HEADERS} ${TEST_HEADERS})

target_include_directories(husky PRIVATE "src/")
target_include_directories(tests PRIVATE "src/" "tests/")

target_link_libraries(tests husky)
