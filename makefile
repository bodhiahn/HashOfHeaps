CXX = g++
CXXFLAGS = -Wall

test: car.h heap.h mytest.cpp
	$(CXX) $(CXXFLAGS) car.h heap.h mytest.cpp -o test

run:
	./test