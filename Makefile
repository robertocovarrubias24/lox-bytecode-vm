CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = main.cpp vm.cpp chunk.cpp debug.cpp value.cpp scanner.cpp compiler.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o loxvm

clean:
	rm -f loxvm