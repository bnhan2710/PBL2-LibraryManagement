CXX = g++

CXXFLAGS = -Wall -std=c++11

SRC_DIR = src
UTILS_DIR = utils

SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/main.cpp)


OUTPUT = program

clean:
	rm -f $(OUTPUT)

run:
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC_FILES)
	./$(OUTPUT)