cmake_minimum_required(VERSION 3.0.0)

project(Patterns CXX)

set(PATTERNS_EXTERN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
if (NOT EXISTS ${PATTERNS_EXTERN_DIR}/GSL/tests)
	execute_process(COMMAND git submodule update --init WORKING_DIRECTORY "${PATTERNS_EXTERN_DIR}")
endif()
add_subdirectory(${PATTERNS_EXTERN_DIR}/GSL)

if (NOT TARGET UnitTest++)
	if (NOT EXISTS ${PATTERNS_EXTERN_DIR}/unittest-cpp/tests)
		execute_process(COMMAND git submodule update --init WORKING_DIRECTORY "${PATTERNS_EXTERN_DIR}")
	endif()
	add_subdirectory(${PATTERNS_EXTERN_DIR}/unittest-cpp)
endif ()

enable_testing()

add_subdirectory(tests)
