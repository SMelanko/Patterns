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

function(PatternTestImpl class name)
	set(test_name ${name}Tests)
	add_executable(${test_name}
		${Patterns_HEADERS}
		../src/${class}/${name}.cpp
		${test_name}.cpp
	)
	target_link_libraries(${test_name} UnitTest++)
	install(TARGETS ${test_name} RUNTIME DESTINATION bin)
	add_test(${test_name} ${test_name})
endfunction()

set(CreationalList
	AbstractFactory Builder FactoryMethod ObjectPool Prototype Singleton)
foreach(creational_pattern ${CreationalList})
	PatternTestImpl(creational ${creational_pattern})
endforeach()

set(StructuralList
	Adapter Bridge Composite Decorator Facade Flyweight Proxy)
foreach(structural_pattern ${StructuralList})
	PatternTestImpl(structural ${structural_pattern})
endforeach()

set(BehavioralList
	ChainOfResponsibility Command Iterator Observer State Strategy TemplateMethod)
foreach(behavioral_pattern ${BehavioralList})
	PatternTestImpl(behavioral ${behavioral_pattern})
endforeach()
