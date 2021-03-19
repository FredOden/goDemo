#include "color.h"
#include "screen.h"
#include "ansi.h"
#include <iostream>


int main(int argc, char **argv) {
	std::cout << "testAnsi::Starting\n";
	Lourah::screen::Ansi ansi;
	Lourah::screen::AColor red = Lourah::screen::AColor(255, 0, 0);
	Lourah::screen::AColor cyan = Lourah::screen::AColor(0, 127, 192);

	ansi.clear();


	ansi.spotXY(10, 10, red);
	ansi.spotXY(10, 12, cyan);

	ansi.flush();
	std::cout << std::endl;
}
