
cmake_minimum_required(VERSION 3.25)

project(AoC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(emlabcpp)

find_package(GTest REQUIRED)
find_package(Boost 1.70 REQUIRED system program_options)
find_package(Eigen3 REQUIRED NO_MODULE)

function(setup_exe target)
	target_compile_options(${target} PRIVATE -O3 -g -Wall -Wextra)
	target_include_directories(${target} PRIVATE ./)
	target_link_libraries(${target} PRIVATE emlabcpp)
endfunction()

add_executable(01 01/main.cpp)
setup_exe(01)
