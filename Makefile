.cpp.o:
	c++ -o $@ -c $<

all:demoCpp

screen/ansi.o: screen/ansi.cpp screen/color.h screen/screen.h screen/ansi.h

demo.o: demo.cpp screen/ansi.h

demoCpp: demo.o screen/ansi.o
	c++ -o $@ $< screen/ansi.o
