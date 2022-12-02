
cmake_minimum_required(VERSION 3.25)

project(AoC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(emlabcpp)

find_package(GTest REQUIRED)
find_package(Boost 1.70 REQUIRED system program_options)
find_package(Eigen3 REQUIRED NO_MODULE)

# Compilation step for static resources
function(add_resources out_var)
  # NOTE: stolen from a blogpost which I forgot to link /o\  
  set(result)
  foreach(in_f ${ARGN})
    file(RELATIVE_PATH src_f ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${in_f})
		set(out_f "${PROJECT_BINARY_DIR}/${in_f}.o")
    add_custom_command(OUTPUT ${out_f}
      COMMAND ld -r -b binary -o ${out_f} ${src_f}
      DEPENDS ${in_f}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "Building GLSL object ${out_f}"
      VERBATIM
      )
    list(APPEND result ${out_f})
  endforeach()
  set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

function(setup_exe target)
	target_compile_options(${target} PRIVATE -O3 -g -Wall -Wextra)
	target_include_directories(${target} PRIVATE ./)
	target_link_libraries(${target} PRIVATE emlabcpp)
endfunction()

add_resources(01_resources 01/input)
add_executable(01_bin 01/main.cpp ${01_resources})
setup_exe(01_bin)

add_resources(02_resources 02/input)
add_executable(02_bin 02/main.cpp ${02_resources})
setup_exe(02_bin)
