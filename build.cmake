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

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${SOURCE_DIRECTORY}>
		$<INSTALL_INTERFACE:src>
)

# dependencies
include(${COMMON_LIBRARY_DIRECTORY}/glfw.cmake)
include(${COMMON_LIBRARY_DIRECTORY}/quill.cmake)
include(${COMMON_LIBRARY_DIRECTORY}/argparse.cmake)

if(BUILD_GRAPHICS)
	target_compile_definitions(${PROJECT_NAME} PUBLIC QUARK_GRAPHICS)
	include(graphics/build.cmake)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
	glfw
	quill::quill
	argparse::argparse
)

add_modules(${PROJECT_NAME}
	src/quark.ixx
	src/log/module.ixx
	src/log/loggers.ixx
	src/config/module.ixx
	src/config/os.ixx
	src/config/directories.ixx
	src/utility/module.ixx
	src/utility/clock.ixx
)

add_sources(${PROJECT_NAME}
	src/quark.cxx
)
