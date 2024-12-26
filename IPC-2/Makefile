# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target binary
TARGET = prime-calculator

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): prime-calculator.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) prime-calculator.cpp

# Clean up generated files
clean:
	rm -f $(TARGET)
