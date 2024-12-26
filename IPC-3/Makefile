# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread

# Output files
TARGETS = first second

all: $(TARGETS)

first: first.cpp shared_array.cpp
	$(CXX) $(CXXFLAGS) -o first first.cpp shared_array.cpp

second: second.cpp shared_array.cpp
	$(CXX) $(CXXFLAGS) -o second second.cpp shared_array.cpp

clean:
	rm -f $(TARGETS)

.PHONY: all clean
