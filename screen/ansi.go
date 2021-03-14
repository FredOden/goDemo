package screen

import (
	"fmt"
)


const defaultSpot =  "\x1b[1mX";

type Ansi struct {
	buffer string;
	spot string;
}

func NewAnsi() *Ansi { s:= &Ansi{buffer: "", spot: defaultSpot}; return s; }

func (screen *Ansi) SetText(x, y int, color *AColor, text string) {
	var r,g,b byte;
	r=127;g=127;b=127;
	if (color != nil) {
		r = color[R]; g = color[G]; b = color[B];
	}
	screen.buffer += fmt.Sprintf("\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%s\x1b[0m", y, x, r, g, b, text);
}

func (screen *Ansi) SpotXY(x, y int, color *AColor) {
	var r,g,b byte;
	r=127;g=127;b=127;
	if (color != nil) {
		r = color[R]; g = color[G]; b = color[B];
	}
	screen.buffer += fmt.Sprintf("\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%s\x1b[0m", y, x, r, g, b, screen.spot);
}

func (screen *Ansi) Clear() {
	screen.buffer = "\x1b[2J";
}

func (screen *Ansi) Flush() {
	fmt.Print(screen.buffer);
}

func (screen *Ansi) SetSpot(spot string) { screen.spot = spot; }
func (screen *Ansi) GetSpot() string { return screen.spot }


