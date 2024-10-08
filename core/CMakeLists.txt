cmake_minimum_required(VERSION 3.28)

project(
	quark_core
	VERSION 0.0.0
	LANGUAGES CXX
)

set(SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/src)

if(BUILD_SHARED_LIBS)
	set(LIBRARY_TYPE SHARED)
else()
	set(LIBRARY_TYPE STATIC)
endif()

add_library(${PROJECT_NAME} ${LIBRARY_TYPE})
add_library(quark::core ALIAS ${PROJECT_NAME})

include(build.cmake)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${SOURCE_DIRECTORY}>
		$<INSTALL_INTERFACE:src>
)

# dependencies
include(${COMMON_LIBRARY_DIRECTORY}/glfw.cmake)
include(${COMMON_LIBRARY_DIRECTORY}/glad.cmake)
include(${COMMON_LIBRARY_DIRECTORY}/quill.cmake)

glad_add_library(glad_gl_core_mx_33 REPRODUCIBLE MX API gl:core=3.3)

target_link_libraries(${PROJECT_NAME} PUBLIC
	glfw
	glad_gl_core_mx_33
	quill::quill)
