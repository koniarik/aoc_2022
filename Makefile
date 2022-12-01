.DEFAULT_GOAL := build
.PHONY: build build_host build_g4

FIND_FILTER = -not \( -path ./build -prune \) -not \( -path ./emlabcpp -prune \) -not \( -path ./emlabcpp_drivers -prune \) -not \( -path ./stm32-cmake -prune \) -not \( -path ./.doxygen -prune \) 

BUILD_ARGS = -GNinja

01: build
	build/01 01/input

build:
	cmake -Bbuild ${BUILD_ARGS} 
	cmake --build build/ -j 4

test: build
	cd build/ && ctest -T Test --output-on-failure

list-variables:
	@echo $(foreach \
		v, \
		$(.VARIABLES), \
		$(if \
			$(filter file, $(origin $(v))), \
			\\n$(v)=$($(v)), \
			$(if \
				$(filter command line, $(origin $(v))), \
				\\n$(v)=$($(v)), \
				$(if \
					$(filter override, $(origin $(v))), \
					\\n$(v)=$($(v)))))) | egrep -v '^$$' | egrep -v '=\s*$$' | sort

list-targets:
	@egrep "^[A-Za-z0-9_-]+\:([^\=]|$$)" $(lastword $(MAKEFILE_LIST)) | sed -E 's/(.*):.*/\1/g' | sort

clang-format:
	find ./ ${FIND_FILTER} \( -iname "*.h" -o -iname "*.cpp" -o -iname "*.hpp" \)  | xargs clang-format -i

cmake-format:
	find ./ ${FIND_FILTER} \( -iname "*CMakeLists.txt" -o -iname "*.cmake" \) | xargs cmake-format -i
