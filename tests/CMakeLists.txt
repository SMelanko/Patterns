cmake_minimum_required(VERSION 3.0.2)

project(PatternsTests CXX)

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
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. "
			"Please use a different C++ compiler.")
	endif ()
endif ()

function(AppendPatternTest src_file_name)
	add_executable(${src_file_name}
		${src_file_name}.cpp
		${Patterns_HEADERS}
		${Patterns_SOURCES}
	)
	target_link_libraries(${src_file_name} UnitTest++)
	install(TARGETS ${src_file_name} RUNTIME DESTINATION bin)
	add_test(${src_file_name} ${src_file_name})
endfunction()

AppendPatternTest(AbstractFactoryTests)
AppendPatternTest(BuilderTests)
AppendPatternTest(FactoryMethodTests)
AppendPatternTest(ObjectPoolTests)
AppendPatternTest(PrototypeTests)
AppendPatternTest(SingletonTests)

AppendPatternTest(AdapterTests)
AppendPatternTest(BridgeTests)
AppendPatternTest(CompositeTests)
AppendPatternTest(DecoratorTests)
AppendPatternTest(FacadeTests)
