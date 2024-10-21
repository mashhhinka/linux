CXX = g++

CXXFLAGS = -Wall -g

TARGET = program

OBJECTS = main.o ComplexNumber.o sort_complex.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp ComplexNumber.h sort_complex.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ComplexNumber.o: ComplexNumber.cpp ComplexNumber.h
	$(CXX) $(CXXFLAGS) -c ComplexNumber.cpp

sort_complex.o: sort_complex.cpp sort_complex.h
	$(CXX) $(CXXFLAGS) -c sort_complex.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)
