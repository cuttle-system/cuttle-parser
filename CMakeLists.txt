cmake_minimum_required(VERSION 3.0.2)

file(GLOB SRCS "src/*.cpp")
file(GLOB TEST_SRCS "tests/*.cpp")

file(GLOB HEADERS "src/*.hpp")
file(GLOB TEST_HEADERS "tests/*.hpp")

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -std=c++17")

add_library(husky SHARED ${SRCS})
add_executable(tests ${TEST_SRCS})

target_link_libraries(tests husky)
