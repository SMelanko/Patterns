cmake_minimum_required(VERSION 3.0.2)

project(Patterns CXX)

set(PATTERNS_SUBMOD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
if (NOT EXISTS ${PATTERNS_SUBMOD_DIR}/GSL/tests)
	execute_process(COMMAND git submodule update --init WORKING_DIRECTORY "${PATTERNS_SUBMOD_DIR}")
endif()
add_subdirectory(${PATTERNS_SUBMOD_DIR}/GSL)

if (NOT TARGET UnitTest++)
	if (NOT EXISTS ${PATTERNS_SUBMOD_DIR}/unittest-cpp/tests)
		execute_process(COMMAND git submodule update --init WORKING_DIRECTORY "${PATTERNS_SUBMOD_DIR}")
	endif()
	add_subdirectory(${PATTERNS_SUBMOD_DIR}/unittest-cpp)
endif ()

set(Patterns_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(Behavioral_INCLUDE_DIR ${Patterns_INCLUDE_DIR}/behavioral)
set(Creatinal_INCLUDE_DIR ${Patterns_INCLUDE_DIR}/creational)
set(Structural_INCLUDE_DIR ${Patterns_INCLUDE_DIR}/structural)
file(GLOB Behavioral_HEADERS "${Behavioral_INCLUDE_DIR}/*.h")
file(GLOB Creatinal_HEADERS "${Creatinal_INCLUDE_DIR}/*.h")
file(GLOB Structural_HEADERS "${Structural_INCLUDE_DIR}/*.h")

set(Patterns_HEADERS
	${Behavioral_HEADERS}
	${Creatinal_HEADERS}
	${Structural_HEADERS}
)

set(Patterns_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
aux_source_directory(${Patterns_SRC_DIR}/behavioral Behavioral_SOURCES)
aux_source_directory(${Patterns_SRC_DIR}/creational Creatinal_SOURCES)
aux_source_directory(${Patterns_SRC_DIR}/structural Structural_SOURCES)

set(Patterns_SOURCES
	${Behavioral_SOURCES}
	${Creatinal_SOURCES}
	${Structural_SOURCES}
)

include_directories(
	${Patterns_INCLUDE_DIR}
	${PATTERNS_SUBMOD_DIR}/GSL
	${PATTERNS_SUBMOD_DIR}/unittest-cpp)

enable_testing()

add_subdirectory(tests)
