CXX=g++
CXXFLAGS=-Wall -std=c++11
SRC_DIR=src
OBJ_DIR=obj
LIB_NAME=build/scui.a

SRCS=$(wildcard $(SRC_DIR)/**/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: build $(LIB_NAME) test

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

build/tests/init_test: Test/test_init.cpp $(LIB_NAME) | build/tests
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIB_NAME)

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
	rm -rf $(OBJ_DIR) $(LIB_NAME) build

test: build/tests/init_test
	./build/tests/init_test

targets:
	@echo "This is a list of all make targets"
	@echo "make all\t\tBuild and test everything automatically"
	@echo "make $(LIB_NAME)\tBuild the library"
	@echo "make test\t\tBuild and run all tests"
	@echo "make clean\t\tRemove all the built files"

.PHONY: all clean test
