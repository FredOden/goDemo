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
				Pixel(const APoint& p, const screen::AColor& color) { p3d = p; this->color = color; projected = false; }
				Pixel(const Pixel& pixel) {
					p3d = pixel.p3d;
					p2d = pixel.p2d;
					projected = pixel.projected;
					color = pixel.color;
				}
				char *toString() {
					static char ret[1000];
					sprintf(ret, "p3d(%g,%g,%g), p2d(%g,%g), color(%d,%d,%d), %s", p3d[0],p3d[1],p3d[2], p2d[0], p2d[1], color.rgba[0], color.rgba[1], color.rgba[2], projected?"True":"False");
					return ret;
				}
		};


		class Shape {
			private:
				int length = 0;
				int *count;
			public:
				Pixel *pixels;
				Shape() { length = 0; pixels = NULL; count = (int *)malloc(sizeof(int)); *count = 0; }
				Shape& operator = (const Shape& shape) {
				// Copy constructor: shallow copy, it is a copy don't free pixels when deleted
					(*shape.count)++;
					if (count == shape.count && pixels == shape.pixels) {
						//std::cerr << "Shape::SAME COPY::" << shape.pixels << " -> " << pixels << "::length::"  << length << std::endl;
						(*count)++;
						return *this;
					}
					if ((*count) > 0) {
						// Tell my twins that I am leaving the team
						(*count)--;
					} else {
						free(pixels);
						//std::cerr << "Shape delete::THE ULTIMATE FREE::"  << pixels << "::length::" << length << "::count::" << *count << std::endl;
						pixels = NULL;
					}
					length = shape.length;
					pixels = shape.pixels;
					count = shape.count;
					//std::cerr << "Shape::SHALOW COPY::" << shape.pixels << " -> " << pixels << "::length::"  << length << std::endl;
					return *this;
				}
				// Assignment : deep copy, it is not a shallow copy so free pixels when deleted
				Shape(const Shape& shape) {
					pixels = (Pixel *)malloc(sizeof(Pixel)*shape.length);
					length = shape.length;
					count = (int *)malloc(sizeof(int)); *count = 0;
					memcpy((void *)pixels, (void *)shape.pixels, sizeof(Pixel)*length);
					//std::cerr << "Shape::DEEP COPY::"  << shape.pixels << " -> " << pixels << "::length::" << length << std::endl;
				}
				~Shape() {
					if (length) {
						if ((*count) == 0) {
							free(pixels);
							//std::cerr << "Shape delete::FREE::"  << pixels << "::length::" << length << "::count::" << *count << std::endl;
						} else {
							(*count)--;
							//std::cerr << "Shape delete::DEREF::"  << pixels << "::length::" << length << "::count::" << *count << std::endl;
						}
					}
				}
				Shape& operator += (const Pixel& pixel) {
					pixels = (Pixel *)((length == 0)?malloc(sizeof(Pixel)):realloc(pixels, sizeof(Pixel)*(length + 1)));
					pixels[length++] = pixel;
					return *this;
				}
				inline int getLength() const { return length; }
				inline Pixel& operator [] (int i) const { return pixels[i]; }
		};


		class Renderer {
			protected:
				double halfWidth; // cached computation of width/2
				double halfHeight; // cached computation of height/2
				double width; // cached cast to float64 for further computation
				double height; // cached cast to float64 for further computation
				APoint camera; // Where is the camera (fixing [0,0,0] point) a simple implementation
				Pixel **zP;   // Zdepth pixels indexed by X2D%width + Y2D/width if p3d[Z] > existing pixel
				int length;
				void project(Pixel &); // projection according to the renderer class

			public:
				Renderer(int iWidth, int iHeight, const APoint& camera) {
					width = (double)iWidth;
					height = (double)iHeight;
					length = (iWidth + 1)*(iHeight + 1);
					halfWidth = width/2;
					halfHeight = height/2;
					this->camera = camera;
					zP = (Pixel **)malloc(sizeof(Pixel *)*length);
					for(int i = 0; i < length; i++) zP[i] = NULL;
				}
				~Renderer() {
					free(zP);
				}
				void render(const Shape &);
				// Rotate apply rotation through 3 angles
				// rX rotation around absolute x axis
				// rY rotation around absolute y axis
				// rZ rotation around absolute z axis
				Shape rotate(const Shape& , double rX, double rY, double rZ);
				// Draw draw the full content of zP buffer of the renderer
				// then clears the content of zP
				void draw(Lourah::screen::Screen& screen);
				Shape translate(const Shape&, const AVector&); 
		};

	}
}
#endif
