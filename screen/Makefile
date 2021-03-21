CCFLAGS=-O3

all:testAnsi

ansi.o:ansi.cpp screen.h color.h ansi.h
	c++ $(CCFLAGS) -c $<

testAnsi:testAnsi.cpp ansi.o
	c++ $(CCFLAGS) -o testAnsi $< ansi.o
