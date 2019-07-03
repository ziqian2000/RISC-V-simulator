PROGRAM = code

CXX = g++
CXXFLAGS = -g -std=c++17

CPP_FILES = $(wildcard code/*.cpp)
H_FILES = $(wildcard code/*.h)

LDOPTIONS = -L.

$(PROGRAM): $(CPP_FILES) $(H_FILES) 
	$(CXX) -O2 -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES)
