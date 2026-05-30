# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = $(shell find . -name "*.cpp")
HEADERS = $(shell find . -name "*.h")
TARGET = program

# Default rule: just compile
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)

# Shortcut to compile and run
run: $(TARGET)
	./$(TARGET)

# Shortcut to clean up the executable
clean:
	rm -f $(TARGET)
