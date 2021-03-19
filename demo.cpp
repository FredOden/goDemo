
#include "screen/color.h"
#include "screen/screen.h"
#include "screen/ansi.h"
#include <iostream>


int main(int argc, char **argv) {
	std::cout << "DemoCpp::Starting\n";
	Lourah::screen::Ansi ansi;
	Lourah::screen::AColor red = Lourah::screen::AColor(255, 0, 0);

	ansi.clear();


	ansi.spotXY(10, 10, red);

	ansi.flush();
}
