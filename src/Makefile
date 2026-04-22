CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

BUILD_DIR = ../build
SRC_DIR = .

# Qt6
PKG_CONFIG_PATH := /run/host/usr/lib64/pkgconfig
export PKG_CONFIG_PATH
MOC       = /run/host/usr/lib64/qt6/libexec/moc
QT_CFLAGS = $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS   = $(shell pkg-config --libs   Qt6Widgets)

CALC_SRCS   = $(filter-out math_lib_tests.cpp stddev.cpp, $(wildcard *.cpp))
STDDEV_SRCS = stddev.cpp math_lib.cpp
TEST_SRCS   = math_lib_tests.cpp math_lib.cpp
PARSER_SRCS = parser.cpp math_lib.cpp parser_main.cpp

CALC_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CALC_SRCS))
STDDEV_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(STDDEV_SRCS))
TEST_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))
PARSER_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(PARSER_SRCS))

.PHONY: all stddev test clean parser

all: $(BUILD_DIR)/calculator

stddev: $(BUILD_DIR)/stddev

parser: $(BUILD_DIR)/parser

gui.moc: gui.cpp
	$(MOC) gui.cpp -o gui.moc

$(BUILD_DIR)/gui.o: gui.cpp gui.moc
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(QT_CFLAGS) -c gui.cpp -o $@

$(BUILD_DIR)/calculator: $(CALC_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ $(QT_LIBS) -o $@

$(BUILD_DIR)/stddev: $(STDDEV_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/tests: $(TEST_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lpthread

$(BUILD_DIR)/parser: $(PARSER_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f gui.moc
