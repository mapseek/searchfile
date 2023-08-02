CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
BUILD_DIR := build

# Library
LIBRARY_SRC := search_file.cpp
LIBRARY_OBJ := $(addprefix $(BUILD_DIR)/,$(LIBRARY_SRC:.cpp=.o))
LIBRARY_NAME := $(BUILD_DIR)/libsearch_file.a

# Main program
MAIN_SRC := main.cpp
MAIN_OBJ := $(addprefix $(BUILD_DIR)/,$(MAIN_SRC:.cpp=.o))
EXECUTABLE := $(BUILD_DIR)/main

.PHONY: all clean

all: create_build_dir $(LIBRARY_NAME) $(EXECUTABLE)

create_build_dir:
	mkdir -p $(BUILD_DIR)

$(LIBRARY_NAME): $(LIBRARY_OBJ)
	ar rcs $(LIBRARY_NAME) $(LIBRARY_OBJ)

$(EXECUTABLE): $(MAIN_OBJ) $(LIBRARY_NAME)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(MAIN_OBJ) -L$(BUILD_DIR) -lsearch_file

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

