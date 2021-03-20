/*
func Append(shape []*Pixel, p3d *APoint, color *screen.AColor) []*Pixel {
	p:=&Pixel{p3d:p3d, color:color, projected:false};
	return append(shape, p);
}
*/
#include <iostream>
#include <cmath>
#include "matrix.h"
#include "renderer.h"

// project "protected" method to project the 3d representation in
// the 2d pane of the renderer
void Lourah::geometry::Renderer::project(Pixel& p) {
	if  (p.projected) {
		return;
	}
	APoint cam = camera;
	double k = cam[Lourah::geometry::APoint::Z]/(p.p3d[Lourah::geometry::APoint::Z] + cam[Lourah::geometry::APoint::Z]);
	double x2d = (halfWidth + ((p.p3d[Lourah::geometry::APoint::X] - camera[Lourah::geometry::APoint::X])*k + camera[Lourah::geometry::APoint::X]));
	double y2d = (halfHeight - ((p.p3d[Lourah::geometry::APoint::Y] - camera[Lourah::geometry::APoint::Y])*k + camera[Lourah::geometry::APoint::Y]));
	APoint p2d(x2d, y2d, 0);
	p.p2d = p2d;
	p.projected = true;
}

// Render the shape (array of pixels)
void Lourah::geometry::Renderer::render(Lourah::geometry::Shape& shape) {
	for (int i= 0; i < shape.getLength(); i++) {
		Lourah::geometry::Pixel pixel = shape[i];
		if (!pixel.projected) {
			project(pixel);
		}
		Lourah::geometry::APoint w = pixel.p2d;


		if (
				(w[Lourah::geometry::APoint::X] < 0 || w[Lourah::geometry::APoint::X]  > width)
				|| (w[Lourah::geometry::APoint::Y] < 0 || w[Lourah::geometry::APoint::Y] > height)
		   ) { continue; }

		//std::cout << "w[0]::" << w[0] << "::w[1]::" << w[1] << std::endl;
		int wP =  (int)(w[Lourah::geometry::APoint::X] + w[Lourah::geometry::APoint::Y]*width);

		//std::cout << "   wP::" << wP << std::endl;

		if (zP[wP] == NULL || zP[wP]->p3d[Lourah::geometry::APoint::Z] <= pixel.p3d[Lourah::geometry::APoint::Z]) {
			zP[wP] = new Lourah::geometry::Pixel(pixel);
			//std::cout << "zP[" << wP << "]::" << zP[wP]->toString() << std::endl;
		}
	}
}

// Rotate apply rotation through 3 angles
// rX rotation around absolute x axis
// rY rotation around absolute y axis
// rZ rotation around absolute z axis
Lourah::geometry::Shape& Lourah::geometry::Renderer::rotate(Shape &shape, double rX, double rY, double rZ) {
	Lourah::geometry::AMatrix mr(rX, rY, rZ);
	Lourah::geometry::APoint p;
	for (int i=0 ; i < shape.getLength(); i++) {
		p = shape[i].p3d;
		shape[i].projected = false;
		shape[i].p3d = mr * p; //shape[i].p3d;
	}
	return shape;
}

Lourah::geometry::Shape& Lourah::geometry::Renderer::translate(Shape &shape, AVector& vector) {
	for (int i=0; i < shape.getLength(); i++) {
		shape[i].p3d = shape[i].p3d.translate(vector);
	}
	return shape;
}

// Draw draw the full content of zP buffer of the renderer
// then clears the content of zP
void Lourah::geometry::Renderer::draw(Lourah::screen::Screen& screen) {
	screen.clear();
	for (int i = 0; i < length; i++) {
		//if (i==4600) std::cout << "zP[" << i << "]::" << zP[i] << std::endl;
		if (zP[i] != NULL  && zP[i]->projected) {
			int x = int(zP[i]->p2d[Lourah::geometry::APoint::X] + .5);
			int y = int(zP[i]->p2d[Lourah::geometry::APoint::Y] + .5);
			//std::cout << "x::" << x << "::y::" << y << std::endl;
			screen.spotXY(x, y, zP[i]->color);
			zP[i] = NULL;
		}
	}
	screen.flush();
}


