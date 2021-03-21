#ifndef LOURAH_SCREEN_ANSI_H
#define LOURAH_SCREEN_ANSI_H
#include <string>

namespace Lourah {
	namespace screen {
		class Ansi : public Screen {
			private:
				std::string spot;
				char *buffer;
				int pos;
			public:
				Ansi();
				~Ansi();
				void clear();
				void flush(bool bFlush = false); // bFlush == true means flush content to stdout
				void spotXY(int, int, AColor&);
				void setText(int, int, AColor&, std::string);
				inline std::string getSpot() { return spot; };
				inline void getSpot(std::string spot) { this->spot = spot; };
		};
	}
}
#endif
