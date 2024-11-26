CPP=/usr/bin/g++
CPP_STANDARD=-std=c++23
CPP_OPTIMIZATION_LEVEL=-O3
CPP_WARNING=-Wall -Wextra -Wconversion -Wpedantic -Wshadow
CPP_INCLUDE=-Iinclude
CPP_FLAGS=$(CPP_STANDARD) $(CPP_OPTIMIZATION_LEVEL) $(CPP_WARNING) $(CPP_INCLUDE)

BUILD_DIR=./build

# Cleans build directory
clean:
	rm -f $(BUILD_DIR)/**

# Build target day00
$(BUILD_DIR)/day00: ./src/main.cpp ./src/solutions/day00.cpp
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CPP_FLAGS) -o $@ $^

# Run target day00
run-day00: $(BUILD_DIR)/day00
	$< src/input/day00.txt $(ARGS)
