# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = interactive-shell
SRC = interactive-shell.cpp

# Targets
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
