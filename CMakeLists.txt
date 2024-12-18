cmake_minimum_required(VERSION 3.15...3.31)

project(numerical_analysis_project)


add_executable(${PROJECT_NAME} 
	src/calculus.cpp
	src/matrix.cpp
	src/numerical.cpp
	vs_cpp_NA.cpp
)

target_include_directories(target 
	PRIVATE
		${PROJECT_SOURCE_DIR}/include	
)