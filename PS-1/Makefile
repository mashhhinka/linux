CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
LDFLAGS =

TARGET = do-command
OBJS = do-command.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

do-command.o: do-command.cpp
	$(CXX) $(CXXFLAGS) -c do-command.cpp

clean:
	rm -f $(TARGET) $(OBJS)
