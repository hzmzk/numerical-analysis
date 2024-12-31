cmake_minimum_required(VERSION 3.15...3.31)

project(numerical_analysis_project)

add_executable(${PROJECT_NAME} 
	src/calculus.cpp
	src/matrix.cpp
	src/numerical.cpp
	src/probability.cpp
	"main.cpp"
)

target_include_directories(${PROJECT_NAME} 
	PRIVATE
		${PROJECT_SOURCE_DIR}/include	
)