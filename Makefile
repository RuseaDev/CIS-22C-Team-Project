# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)
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
