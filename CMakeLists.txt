cmake_minimum_required(VERSION 3.28)

project(quark)

macro(add_sources target)
	foreach(SOURCE_FILE ${ARGV})
		list(APPEND ADD_SOURCES "${CMAKE_CURRENT_LIST_DIR}/${SOURCE_FILE}")
	endforeach()
	list(REMOVE_AT ADD_SOURCES 0)

	target_sources(${target} PUBLIC ${ADD_SOURCES})
	unset(ADD_SOURCES)
endmacro()

macro(add_modules target)
	foreach(SOURCE_FILE ${ARGV})
		list(APPEND ADD_SOURCES "${CMAKE_CURRENT_LIST_DIR}/${SOURCE_FILE}")
	endforeach()
	list(REMOVE_AT ADD_SOURCES 0)

	target_sources(${target} PUBLIC
		FILE_SET CXX_MODULES
		FILES ${ADD_SOURCES})
	set_source_files_properties(${ADD_SOURCES} PROPERTIES LANGUAGE CXX)
	unset(ADD_SOURCES)
endmacro()

# global options
string(TIMESTAMP CURRENT_DATE "%Y-%m-%d")
string(TIMESTAMP CURRENT_TIME "%H:%M:%S")

execute_process(COMMAND git describe --tags --always
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	OUTPUT_VARIABLE GIT_REVISION
	OUTPUT_STRIP_TRAILING_WHITESPACE)

set(BUILD_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(COMMON_DIRECTORY ${PROJECT_SOURCE_DIR}/common)
set(COMMON_LIBRARY_DIRECTORY ${COMMON_DIRECTORY}/lib)

# cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 26)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-DDEBUG")

# global defines
add_compile_definitions(BUILD_DATE=${CURRENT_DATE})
add_compile_definitions(BUILD_TIME=${CURRENT_TIME})
add_compile_definitions(BUILD_REVISION=${GIT_REVISION})

if(UNIX AND NOT APPLE)
	add_compile_definitions(LINUX)
elseif(APPLE)
	add_compile_definitions(APPLE)
elseif(WIN32 OR MSVC OR MSYS OR MINGW)
	add_compile_definitions(WINDOWS)
endif()

# global compilation flags
add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fstack-protector>")

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT WIN32)
 	add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=undefined>")
	add_link_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=undefined>")

    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=function>")
    add_link_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=function>")

    #add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=leak>")
    #add_link_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=leak>")

    # ASan seems broken with GLX or Nix
    #add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=address>")
    #add_link_options("$<$<COMPILE_LANGUAGE:CXX>:-fsanitize=address>")
endif()

# subprojects
include(options.cmake)

if(BUILD_CORE)
	add_subdirectory(core)
endif()

if(BUILD_TESTS)
	add_subdirectory(tests)
endif()
