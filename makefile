PROGRAM = code

CXX = g++
CXXFLAGS = -g -std=c++17

CPP_FILES = $(wildcard RISCV/*.cpp)
H_FILES = $(wildcard RISCV/*.h)

LDOPTIONS = -L.

$(PROGRAM): $(CPP_FILES) $(H_FILES) 
	$(CXX) -O2 -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES)
