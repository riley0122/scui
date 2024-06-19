CXX=g++
CXXFLAGS=-Wall -std=c++11
SRC_DIR=src
OBJ_DIR=obj

ifeq ($(OS),Windows_NT)
	PREFIX=powershell
else
	PREFIX=:
endif

SRCS=$(wildcard $(SRC_DIR)/**/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: build test

build/tests/init_test: Test/test_init.cpp | build/tests
	$(CXX) $(CXXFLAGS) -o $@ $<

build/tests/create_test: Test/test_create.cpp | build/tests
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(PREFIX) mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	$(PREFIX) mkdir -p build

build/tests:
	$(PREFIX) mkdir -p build/tests

$(OBJ_DIR):
	$(PREFIX) mkdir -p $(OBJ_DIR)

clean:
	$(PREFIX) rm -r $(OBJ_DIR) build

test: build/tests/init_test build/tests/create_test
	./build/tests/init_test
	./build/tests/create_test

targets:
	@echo "Using prefix '$(PREFIX)' for os '$(OS)'"
	@echo "This is a list of all make targets"
	@echo "make all\t\tBuild and test everything automatically"
	@echo "make test\t\tBuild and run all tests"
	@echo "make clean\t\tRemove all the built files"

.PHONY: all clean test
