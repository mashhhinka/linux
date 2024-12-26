# Makefile for signal-echo program

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Targets
TARGET = signal-echo
SOURCES = signal-echo.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
