#ifndef LOURAH_GEOMETRY_RENDERER_H
#define LOURAH_GEOMETRY_RENDERER_H
#include <iostream>
#include <stdlib.h>
#include "color.h"
#include "screen.h"
#include "points.h"
namespace Lourah {
	namespace geometry {
		class  Pixel {
			public:
				APoint p3d;    // The #rough 3d point coordinate
				APoint p2d;    // The "projection" of 3d point through a Renderer
				bool projected; // to check if p3d was projected to avoid recomputation
				screen::AColor color;  // RGBA color of the pixel
				//Pixel() { projected = false; }
				Pixel(APoint& p, screen::AColor& color) { p3d = p; this->color = color; projected = false; }
				char *toString() {
					static char ret[1000];
					sprintf(ret, "p3d(%g,%g,%g), color(%d,%d,%d), %s", p3d[0],p3d[1],p3d[2], color.rgba[0], color.rgba[1], color.rgba[2], projected?"True":"False");
					return ret;
				}
		};


		class Shape {
			private:
				int length = 0;
			public:
				Pixel *pixels;
				Shape() { length = 0; pixels = NULL; }
				~Shape() { if (length) free(pixels); }
				Shape& operator += (Pixel& pixel) {
					pixels = (Pixel *)((length == 0)?malloc(sizeof(Pixel)):realloc(pixels, sizeof(Pixel)*(length + 1)));
					pixels[length++] = pixel;
					return *this;
				}
				inline int getLength() { return length; }
				inline Pixel& operator [] (int i) { return pixels[i]; }
		};


		class Renderer {
			protected:
				double halfWidth; // cached computation of width/2
				double halfHeight; // cached computation of height/2
				double width; // cached cast to float64 for further computation
				double height; // cached cast to float64 for further computation
				APoint camera; // Where is the camera (fixing [0,0,0] point) a simple implementation
				Pixel **zP;   // Zdepth pixels indexed by X2D%width + Y2D/width if p3d[Z] > existing pixel
				void project(Pixel &); // projection according to the renderer class

			public:
				Renderer(int width, int height, APoint& camera) {
					this->width = (double)width;
					this->height = (double)height;
					halfWidth = this->width/2;
					halfHeight = this->height/2;
					this->camera = camera;
					zP = (Pixel **)malloc(sizeof(Pixel *)*(width + 1)*(height + 1));
				}
				~Renderer() {
					free(zP);
				}
				void render(Shape &);
				// Rotate apply rotation through 3 angles
				// rX rotation around absolute x axis
				// rY rotation around absolute y axis
				// rZ rotation around absolute z axis
				Shape& rotate(Shape& , double rX, double rY, double rZ);
				// Draw draw the full content of zP buffer of the renderer
				// then clears the content of zP
				void draw(Lourah::screen::Screen& screen);
				Shape& translate(Shape&, AVector&); 
		};

	}
}
#endif
