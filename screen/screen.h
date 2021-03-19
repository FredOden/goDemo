#ifndef LOURAH_SCREEN_SCREEN_H
#define LOURAH_SCREEN_SCREEN_H
#include <string>
namespace Lourah {
	namespace screen {

		// Screen is a basic screen interface with essential methods
		class Screen {
			virtual void spotXY(int x, int y, Lourah::screen::AColor& color) = 0; //SpotXY(x,y int, color *AColor)
			virtual void setText(int x, int y, Lourah::screen::AColor& color, std::string) = 0; //SetText(x,y int, color *AColor, text string)
			virtual void clear() = 0; //Clear()
			virtual void flush() = 0; //Flush()
		};
	}
}
#endif
