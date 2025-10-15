CXX = g++
CFLAGS = -static -I$(PWD)/include
SRDIR := $(PWD)/src/
BUILDDIR := $(PWD)/build/
build: tng
	@mkdir -p $(PWD)/build
	$(CXX) $(CFLAGS) -o $(BUILDDIR)/tng $(SRDIR)/main.o $(SRDIR)/makefile.o

tng: main.o tng_make_file.o handle_args.o
	
main.o:
	$(CXX) $(CFLAGS) -c $(SRDIR)/main.cpp $(SRDIR)/main.o
		
tng_make_file.o:
	$(CXX) $(CFLAGS) -c $(SRDIR)/makefile.o $(SRDIR)/tng_make_file.cpp

handle_args.o:
	$(CXX) $(CFLAGS) -c $(SRDIR)/handle_args.o $(SRDIR)/handle_args.cpp
