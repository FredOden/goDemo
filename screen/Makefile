all:testAnsi

ansi.o:ansi.cpp screen.h color.h ansi.h
	c++ -c $<

testAnsi:testAnsi.cpp ansi.o
	c++ -o testAnsi $< ansi.o
