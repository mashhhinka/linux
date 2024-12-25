CXX = g++
CXXFLAGS = -std=c++17 -pthread -O2 -Wall

TARGET = array_summary
SRC = array_summary.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
