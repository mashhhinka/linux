# Compiler
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
# Executable name
TARGET = redirect-cin
# Build target
all: $(TARGET)
# Build the executable
$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp
# Clean target
clean:
	rm -f $(TARGET)
