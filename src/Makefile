CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

BUILD_DIR = ../build
SRC_DIR = .

CALC_SRCS   = $(filter-out stddev.cpp tests.cpp, $(wildcard *.cpp))
STDDEV_SRCS = stddev.cpp math_lib.cpp
TEST_SRCS   = math_lib_tests.cpp math_lib.cpp

CALC_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CALC_SRCS))
STDDEV_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(STDDEV_SRCS))
TEST_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

.PHONY: all stddev test clean

all: $(BUILD_DIR)/calculator $(BUILD_DIR)/stddev

$(BUILD_DIR)/calculator: $(CALC_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/stddev: $(STDDEV_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/tests: $(TEST_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lpthread

test: $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
