# Makefile
CXX=g++
CXXFLAGS=-Wall -std=c++17
BINARIES: bloomfilters datasets

datasets: datasets.cpp
	${CXX} ${CXXFLAGS} $^ -o $@

bloomfilters: bloomfilters.cpp
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	rm -f ${BINARIES} *.o