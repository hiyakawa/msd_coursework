CXX= c++
CFLAGS= -std=c++11
HEADER= $(wildcard *.h)
OBJS= expr.o parse.o
SRCS= $(wildcard *.cpp)
header= ../headers

msdscript: main.o expr.o parse.o
	$(CXX) $(CFLAGS) -o msdscript $^

test_msdscript: tests.o exec.o
	$(CXX) $(CXXFLAGS) -o test_msdscript tests.o exec.o

libmsdscript.a: $(OBJS)
	ar -ruv libmsdscript.a $(OBJS)

main.o: main.cpp $(header)/cmdline.h catch.h
	c++ -std=c++17 -c -I$(header) main.cpp
	
expr.o: expr.cpp $(header)/expr.h
	$(CXX) $(CFLAGS) -c -I$(header) expr.cpp

parse.o: parse.cpp $(header)parse.h
	$(CXX) $(CFLAGS) -c -I$(header) parse.cpp

exec.o: exec.cpp exec.h
	c++ -c exec.cpp

tests.o: tests.cpp exec.h
	c++ -c tests.cpp

.PHONY: test
test: msdscript
	./msdscript --test

.PHONY: doc
doc:
	cd documentation && doxygen

clean:
	rm msdscript $(wildcard *.o) libmsdscript.a