## Directories to build files into
OBJ_DIR := obj
BIN_DIR := bin

## Executable Name
EXE_NAME = ecs-test

## List of all c++ files to compile
CPP_FILES := $(wildcard *.cpp)

## List of all object files to generate
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(CPP_FILES:%.cpp=%.o))


## Compiler, compiler and linker flags and libaries to use
CXX := g++
FLAGS := -std=c++11 -I /usr/include/python3.4m/ -lboost_python-py34 -lpython3.4m
CXXLIBS := 
LDLIBS := -lboost_python-py34 -lpython3.4m
CXXFLAGS := -std=c++11 -I /usr/include/python3.4m/ $(CXXLIBS) -MMD
LDFLAGS := $(LDLIBS)


## Build the application
all: $(BIN_DIR)/$(EXE_NAME)

$(BIN_DIR)/ecs-test: $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	
## Clean up everything
clean:
	rm -rf obj
	rm -rf bin

## Include auto-generated dependencies rules
-include $(OBJ_FILES:.o=.d)


