CXX=g++
CXXFLAGS=-Wall -std=c++11
SRC_DIR=src
OBJ_DIR=obj

SRCS=$(wildcard $(SRC_DIR)/**/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: build test

build/tests/init_test: Test/test_init.cpp | build/tests
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

build/tests:
	mkdir -p build/tests

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) build

test: build/tests/init_test
	./build/tests/init_test

targets:
	@echo "This is a list of all make targets"
	@echo "make all\t\tBuild and test everything automatically"
	@echo "make test\t\tBuild and run all tests"
	@echo "make clean\t\tRemove all the built files"

.PHONY: all clean test
