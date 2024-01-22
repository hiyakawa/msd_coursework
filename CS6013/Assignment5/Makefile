CXX= /opt/homebrew/opt/llvm/bin/clang++
CFLAGS= -std=c++20
COMPILING= -c
OPENMP_COMPILING= -fopenmp
OPENMP_LINKING= -lomp
OPENMP_LIB_PATH= -L/opt/homebrew/opt/libomp/lib
LINKING= -o

$(info CXX path: $(shell which $(CXX)))

prog: main.o
	$(CXX) $(CFLAGS) main.o $(LINKING) prog $(OPENMP_LIB_PATH) $(OPENMP_LINKING)

main.o: main.cpp
	$(CXX) $(CFLAGS) $(COMPILING) main.cpp

.PHONY: test
test: prog
	./prog