
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

TARGET = hacker-rm

all: $(TARGET)

$(TARGET): hacker-rm.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) hacker-rm.cpp

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) $(FILE)

