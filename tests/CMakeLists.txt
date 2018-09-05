include_directories("../src" ${Boost_INCLUDE_DIR})
link_libraries(cuttle-parser ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

file(GLOB_RECURSE TEST_SRCS "*.cpp")

add_executable(cuttle-parser-tests ${TEST_SRCS})