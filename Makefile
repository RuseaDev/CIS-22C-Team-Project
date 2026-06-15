# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)
TARGET = program
TEST_TARGET = test_runner
TEST_SRC = $(filter-out src/main.cpp,$(SRC)) $(wildcard tests/*.cpp)

# Default rule: just compile
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRC) $(HEADERS)
	$(CXX) $(TEST_SRC) $(CXXFLAGS) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Shortcut to compile and run
run: $(TARGET)
	./$(TARGET)

# Shortcut to clean up the executable
clean:
	rm -f $(TARGET) $(TEST_TARGET)
