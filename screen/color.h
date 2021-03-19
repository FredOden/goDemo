#ifndef LOURAH_SCREEN_ACOLOR_H
#define LOURAH_SCREEN_ACOLOR_H
/*package screen 

  type AColor [4]byte;

  const R = 0;
  const G = 1;
  const B = 2;
  const A = 3;

  func RGB(rgb [3]byte) *AColor { c := &AColor{rgb[0], rgb[1], rgb[2], 255}; return c; }
  */

namespace Lourah {
	namespace screen {

		class AColor {
			public:
				static const int R = 0;
				static const int G = 1;
				static const int B = 2;
				static const int A = 3;
				int rgba[4] = {0, 0, 0, 255};
				inline void RGB(int rgb[3]) {
					rgba[R] = rgb[R];
					rgba[G] = rgb[G];
					rgba[B] = rgb[B];
				}
				AColor() {};
				inline AColor(int r, int g, int b, int a) { rgba[R] = r; rgba[G] = g; rgba[B] = b; rgba[A] = a; };
				inline AColor(int r, int g, int b) { rgba[R] = r; rgba[G] = g; rgba[B] = b; rgba[A] = 255; };
				inline int operator [] (int i) { return rgba[i]; }
		};
	}
}
#endif
