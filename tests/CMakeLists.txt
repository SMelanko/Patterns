cmake_minimum_required(VERSION 3.0.0)

project(PatternsTests CXX)

include_directories(
	../include
	${PATTERNS_EXTERN_DIR}/unittest-cpp
	${PATTERNS_EXTERN_DIR}/GSL
)

if (MSVC14 OR MSVC12) # Has the support we need.
	# Remove unnecessary warnings about unchecked iterators.
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_compile_options(/W4)
else ()
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	if (COMPILER_SUPPORTS_CXX14)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-missing-braces")
	elseif (COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-missing-braces")
	else ()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support."
			"Please use a different C++ compiler.")
	endif ()
endif ()

set (Patterns_HEADERS
	../include/creational/AbstractFactory.h
)

set(Patterns_SOURCES
	../src/creational/AbstractFactory.cpp
)

function(ADD_PATTERNS_TEST name)
	add_executable(${name}
		${name}.cpp
		${Patterns_HEADERS}
		${Patterns_SOURCES}
	)
	target_link_libraries(${name} UnitTest++)
	install(TARGETS ${name}
		RUNTIME DESTINATION bin
	)
	add_test(
		${name}
	  	${name}
	)
endfunction()

ADD_PATTERNS_TEST(AbstractFactoryTests)
