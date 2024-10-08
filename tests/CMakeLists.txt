cmake_minimum_required(VERSION 3.28)

project(
	quark_tests
	LANGUAGES CXX
)

set(SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/src)

# game test
set(TEST_NAME game)
add_executable(${TEST_NAME})
include(${TEST_NAME}/build.cmake)

target_link_libraries(${TEST_NAME} PRIVATE quark::core)
