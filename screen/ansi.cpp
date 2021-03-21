#include "color.h"
#include "screen.h"
#include "ansi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Lourah::screen::Ansi::Ansi() {
	buffer = (char *)malloc(0x100000);
	spot = "\x1b[1mX";
	pos = 0;
}

Lourah::screen::Ansi::~Ansi() {
	free(buffer);
}

void Lourah::screen::Ansi::clear() {
	char const *sClear = "\x1b[2J";
	strcpy(&buffer[pos], sClear);
	pos += strlen(sClear);
}

void Lourah::screen::Ansi::flush(bool bFlush) {
	printf("%s", buffer);
	if (bFlush) fflush(stdout);
	pos = 0; // forget to reset to 0 was BIG bug !!!
}

void Lourah::screen::Ansi::spotXY(int x, int y, Lourah::screen::AColor& color) {
	pos += sprintf(&buffer[pos], "\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%s\x1b[0m", y, x, color[Lourah::screen::AColor::R], color[Lourah::screen::AColor::G], color[Lourah::screen::AColor::B], spot.c_str());
}

void Lourah::screen::Ansi::setText(int x, int y, Lourah::screen::AColor&color, std::string text) {
	pos += sprintf(&buffer[pos], "\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%s\x1b[0m", y, x, color[Lourah::screen::AColor::R], color[Lourah::screen::AColor::G], color[Lourah::screen::AColor::B], text.c_str());
}
