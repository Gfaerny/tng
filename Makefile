CXX = g++
CFLAGS = -static -I$(PWD)/include

build: obj
	@mkdir -p $(PWD)/build
	$(CXX) $(CFLAGS) -o $(PWD)/build/main $(PWD)/src/main.o $(PWD)/src/makefile.o

obj:
	$(CXX) $(CFLAGS) -c $(PWD)/src/main.cpp -o $(PWD)/src/main.o
	$(CXX) $(CFLAGS) -c $(PWD)/src/makefile.cpp -o $(PWD)/src/makefile.o
